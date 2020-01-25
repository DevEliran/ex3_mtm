#include "ParkingLot.h"
#include "Vehicle.h"
#include "UniqueArrayImp.h"
#include "Time.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"
#include "ParkingSpot.h"
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace ParkingLotUtils;
using namespace std;


namespace MtmParkingLot {
    static int const MAX_PAYMENT_MOTOR = 35;
    static int const MAX_PAYMENT_CAR = 70;
    static int const FINE_AMOUNT = 250;
    static int const FIRST_HOUR_FEE_MOTOR = 10;
    static int const HOURLY_FEE_MOTOR = 5;
    static int const FIRST_HOUR_FEE_CAR = 20;
    static int const HOURLY_FEE_CAR = 10;
    static int const HANDICAPPED_FEE = 15;
    static int const MAX_PAYMENT_HOURS = 6;
    static int const MAX_TIME_ALLOWED_TO_PARK = 24;
    static std::map<VehicleType, std::pair<int const, int const>> TypeToFee = {
            {MOTORBIKE, make_pair(FIRST_HOUR_FEE_MOTOR, HOURLY_FEE_MOTOR)},
            {CAR, make_pair(FIRST_HOUR_FEE_CAR, HOURLY_FEE_CAR)},
            {HANDICAPPED, make_pair(HANDICAPPED_FEE, HANDICAPPED_FEE)}
    };
    static std::map<VehicleType, int const> TypeToMaxFee = {
            {MOTORBIKE, MAX_PAYMENT_MOTOR},
            {CAR, MAX_PAYMENT_CAR},
            {HANDICAPPED, HANDICAPPED_FEE}
    };


    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            motorbike_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(
                    parkingBlockSizes[0])),
            car_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(
                    parkingBlockSizes[2])),
            handicapped_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(
                    parkingBlockSizes[1])) {
    }


    bool ParkingLot::isVehicleInLot(LicensePlate licensePlate, VehicleType& type,
                                    unsigned int& index){
        Vehicle v(licensePlate, ParkingSpot(), 0, CAR,
                false);
        if(motorbike_parking.getIndex(v, index)){
            type = MOTORBIKE;
            return true;
        }
        else if(handicapped_parking.getIndex(v, index)){
            type = HANDICAPPED;
            return true;
        }
        else if(car_parking.getIndex(v, index)){
            type = CAR;
            return true;
        }
        return false;
    }


    ParkingResult ParkingLot::enterParking(
            ParkingLotUtils::VehicleType vehicleType,
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time entranceTime) {

        Vehicle vehicle(licensePlate, ParkingSpot(vehicleType),
                        entranceTime, vehicleType, false);
        unsigned int index = 0;
        VehicleType type;
        if(isVehicleInLot(licensePlate, type, index)){
            if(type == MOTORBIKE) {
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                        licensePlate,
                        motorbike_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                        motorbike_parking[vehicle]->vehicleGetParkingSpot());
            }
            else if(type == CAR){
                ParkingLotPrinter::printVehicle(
                        std::cout, vehicleType, licensePlate,
                        car_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                        car_parking[vehicle]->vehicleGetParkingSpot());
            }
            else if(type == HANDICAPPED){
                ParkingLotPrinter::printVehicle(
                        std::cout, vehicleType, licensePlate,
                        handicapped_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                        handicapped_parking[vehicle]->vehicleGetParkingSpot());
            }
            return VEHICLE_ALREADY_PARKED;
        }
        if (vehicleType == MOTORBIKE) {
            try {
                index = motorbike_parking.getFirstEmptyLocation();
                ParkingSpot spot_allocated(vehicleType, index);
                Vehicle v(licensePlate, spot_allocated, entranceTime,
                          vehicleType, false);
                motorbike_parking.insert(v);
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout,
                                                       spot_allocated);
            }
            catch (UniqueArray<Vehicle,
                    Vehicle::compareVehicles>::UniqueArrayIsFullException & e)
            {
                //print according to 3.b
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                licensePlate, entranceTime);
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                return NO_EMPTY_SPOT;
            }
        } else if (vehicleType == HANDICAPPED) {
            try {
                index = handicapped_parking.getFirstEmptyLocation();
                ParkingSpot spot_allocated(vehicleType, index);
                Vehicle v(licensePlate, spot_allocated, entranceTime,
                          vehicleType, false);
                handicapped_parking.insert(v);
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout,
                                                        spot_allocated);

            }
            catch (UniqueArray<Vehicle,
                    Vehicle::compareVehicles>::UniqueArrayIsFullException & e) {
                try {
                    index = car_parking.getFirstEmptyLocation();
                    ParkingSpot spot_allocated1(CAR, index);
                    Vehicle v(licensePlate, spot_allocated1, entranceTime,
                              vehicleType, false);
                    car_parking.insert(v);
                    ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                    licensePlate,
                                                    entranceTime);
                    ParkingLotPrinter::printEntrySuccess(std::cout,
                                                         spot_allocated1);
                }
                catch (UniqueArray<Vehicle,
                        Vehicle::compareVehicles>::UniqueArrayIsFullException &e) {
                    //print according to 3.b
                    ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                    licensePlate, entranceTime);
                    ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                    return NO_EMPTY_SPOT;
                }
            }
        } else if (vehicleType == CAR) {
            try {
                index = car_parking.getFirstEmptyLocation();
                ParkingSpot spot_allocated(vehicleType, index);
                Vehicle v(licensePlate, spot_allocated, entranceTime,
                          vehicleType, false);
                car_parking.insert(v);
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                  licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout,
                                                        spot_allocated);
            }
            catch (UniqueArray<Vehicle,
                    Vehicle::compareVehicles>::UniqueArrayIsFullException & e)
            {
                //print according to 3.b
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                licensePlate, entranceTime);
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                return NO_EMPTY_SPOT;
            }
        }
        return SUCCESS;
    }


     int ParkingLot::calculateFee(Time entryTime, Time exitTime,
                                        VehicleType type,
                                        LicensePlate licensePlate) {
        Time total_time = exitTime - entryTime;
        if(total_time.toHours() == 0){
            return 0;
        }
        const Vehicle v(licensePlate, ParkingSpot(), 0,
                    CAR, false);
        if(type == CAR){
            if(car_parking[v]->isVehicleFined()){
                return FINE_AMOUNT + TypeToMaxFee[type];
            }
        }
        else if (type == MOTORBIKE){
            if(motorbike_parking[v]->isVehicleFined()){
                return FINE_AMOUNT + TypeToMaxFee[type];
            }
        } else if(type == HANDICAPPED){
            if(handicapped_parking[v] != NULL) {
                if (handicapped_parking[v]->isVehicleFined()) {
                    return FINE_AMOUNT + TypeToMaxFee[type];
                }
            } else if(car_parking[v]->isVehicleFined()){
                return FINE_AMOUNT + TypeToMaxFee[type];
            }
        }
        return calculateFeeRecursive(entryTime, exitTime, type, 0, 0);
    }


     int ParkingLot::calculateFeeRecursive(Time entryTime, Time exitTime,
             VehicleType type, int iter, int totalPrice){
        Time total_time_parked = exitTime - entryTime;
        if(total_time_parked.toHours() == 0){
            return totalPrice;
        }
        if(total_time_parked.toHours() == 1) {
            return totalPrice + TypeToFee[type].first;
        }
        if(type == HANDICAPPED){
            if(total_time_parked.toHours() > 0){
                return HANDICAPPED_FEE;
            } else{
                return 0;
            }
        }
        if(total_time_parked.toHours() == MAX_PAYMENT_HOURS){
            return TypeToMaxFee[type];
        }
        totalPrice += TypeToFee[type].second;
        iter += 1;
        Time hour(0,1,0);
        return calculateFeeRecursive(entryTime, exitTime - hour, type, iter,
                                      totalPrice);
    }


    ParkingResult ParkingLot::exitParking(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time exitTime) {

        const Vehicle vehicle(licensePlate, ParkingSpot(), 0,
                        CAR, false);
        unsigned int index;
        if(motorbike_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout,
                    motorbike_parking[vehicle]->getType(),
                    motorbike_parking[vehicle]->getLicensePlate(),
                    motorbike_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout,
                    motorbike_parking[vehicle]->vehicleGetParkingSpot(),
                    exitTime,
                    calculateFee(motorbike_parking[vehicle]->getEntryTime(),
                            exitTime, motorbike_parking[vehicle]->type,
                            licensePlate));
            motorbike_parking.remove(vehicle);
            return SUCCESS;
        }
        else if(handicapped_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout,
                    handicapped_parking[vehicle]->getType(),
                    handicapped_parking[vehicle]->getLicensePlate(),
                    handicapped_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout,
                    handicapped_parking[vehicle]->vehicleGetParkingSpot(),
                    exitTime,
                    calculateFee(handicapped_parking[vehicle]->getEntryTime(),
                            exitTime, handicapped_parking[vehicle]->type,
                            licensePlate));
            handicapped_parking.remove(vehicle);
            return SUCCESS;
        }
        else if(car_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout,
                    car_parking[vehicle]->getType(),
                    car_parking[vehicle]->getLicensePlate(),
                    car_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout,
                    car_parking[vehicle]->vehicleGetParkingSpot(),
                    exitTime,
                    calculateFee(car_parking[vehicle]->entryTime,
                            exitTime, car_parking[vehicle]->getType(),
                            licensePlate));
            car_parking.remove(vehicle);
            return SUCCESS;
        }
        ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }


    ParkingResult ParkingLot::getParkingSpot(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::ParkingSpot &parkingSpot) const {

        unsigned int index;
        Vehicle vehicle(licensePlate, ParkingSpot(), 0, CAR);

        if(car_parking.getIndex(vehicle, index)){
            parkingSpot = car_parking[vehicle]->vehicleGetParkingSpot();
            return SUCCESS;
        }
        if(handicapped_parking.getIndex(vehicle, index)){
            parkingSpot = handicapped_parking[vehicle]->vehicleGetParkingSpot();
            return SUCCESS;
        }
        if(motorbike_parking.getIndex(vehicle, index)){
            parkingSpot = motorbike_parking[vehicle]->vehicleGetParkingSpot();
            return SUCCESS;
        }
        return VEHICLE_NOT_FOUND;
    }


    static bool CompareParkingSpots(const Vehicle* v1, const Vehicle* v2){
        return v1->vehicleGetParkingSpot() < v2->vehicleGetParkingSpot();
    }


    static void fillVehicleVector(vector<Vehicle*>& vehicles, UniqueArray<Vehicle,
                                      Vehicle::compareVehicles> lot){
        const Vehicle* to_copy_vehicle;
        for(unsigned int i = 0; i < lot.getSize(); i++){
            to_copy_vehicle = lot.getElementByIndex(i);
            if(to_copy_vehicle == nullptr){
                continue;
            }
            vehicles.push_back(new Vehicle(*to_copy_vehicle));
        }
    }


    ostream& operator<<(ostream &os, const ParkingLot &parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(os);

        std::vector<Vehicle*> vehicles;

        fillVehicleVector(vehicles, parkingLot.motorbike_parking);
        fillVehicleVector(vehicles, parkingLot.car_parking);
        fillVehicleVector(vehicles, parkingLot.handicapped_parking);

        sort(vehicles.begin(), vehicles.end(), CompareParkingSpots);
        for (Vehicle* v : vehicles) {
            ParkingLotPrinter::printVehicle(os, v->getType(),
                                            v->getLicensePlate(),
                                            v->getEntryTime());
            ParkingLotPrinter::printParkingSpot(os, v->vehicleGetParkingSpot());
        }
        for (Vehicle* v : vehicles){
            delete v;
        }
        return os;
    }


    static int inspectSpecificArea(Time inspectionTime, UniqueArray<Vehicle,
                                      Vehicle::compareVehicles>&lot){
        const Vehicle* temp;
        int count = 0;
        for(unsigned int i = 0; i < lot.getSize(); i++){
            temp = lot.getElementByIndex(i);
            if(temp == nullptr){
                continue;
            }
            else if(!(*temp).isVehicleFined() &&
            (inspectionTime - (*temp).getEntryTime()).toHours() > MAX_TIME_ALLOWED_TO_PARK){
                (*lot[*temp]).setFineTrue();
                count ++;
            }
        }
        return count;
    }


    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        int count1 = 0, count2 = 0, count3 = 0;
        count1 = inspectSpecificArea(inspectionTime, car_parking);
        count2 = inspectSpecificArea(inspectionTime, handicapped_parking);
        count3 = inspectSpecificArea(inspectionTime, motorbike_parking);
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime,
                                              count1+count2+count3);
    }
}