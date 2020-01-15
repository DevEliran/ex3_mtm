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


    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            motorbike_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(parkingBlockSizes[0])),
            car_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(parkingBlockSizes[2])),
            handicapped_parking(UniqueArray<Vehicle, Vehicle::compareVehicles>(parkingBlockSizes[1])) {
    }


    bool ParkingLot::isVehicleInLot(LicensePlate licensePlate, VehicleType& type,
                                    unsigned int& index){
        Vehicle v(licensePlate, ParkingSpot(), 0, CAR, false);
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

        Vehicle vehicle(licensePlate, ParkingSpot(vehicleType), entranceTime, vehicleType, false);
        unsigned int index = 0;
        VehicleType type;
        if(isVehicleInLot(licensePlate, type, index)){
            if(type == MOTORBIKE) {
                ParkingLotPrinter::printVehicle(
                        std::cout, vehicleType, licensePlate, motorbike_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, motorbike_parking[vehicle]->vehicleGetParkingSpot());
            }
            else if(type == CAR){
                ParkingLotPrinter::printVehicle(
                        std::cout, vehicleType, licensePlate, car_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, car_parking[vehicle]->vehicleGetParkingSpot());
            }
            else if(type == HANDICAPPED){
                ParkingLotPrinter::printVehicle(
                        std::cout, vehicleType, licensePlate, handicapped_parking[vehicle]->getEntryTime());
                ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, handicapped_parking[vehicle]->vehicleGetParkingSpot());
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
                ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, spot_allocated);
            }
            catch (UniqueArray<Vehicle, Vehicle::compareVehicles>::UniqueArrayIsFullException & e)
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
                ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, spot_allocated);

            }
            catch (UniqueArray<Vehicle, Vehicle::compareVehicles>::UniqueArrayIsFullException & e) {
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
                catch (UniqueArray<Vehicle, Vehicle::compareVehicles>::UniqueArrayIsFullException &e) {
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
                ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, spot_allocated);
            }
            catch (UniqueArray<Vehicle, Vehicle::compareVehicles>::UniqueArrayIsFullException & e)
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
                                        VehicleType type, Vehicle v) {
        if(type == CAR){
            if(car_parking[v]->isVehicleFined()){
                return calculateFeeRecursive(entryTime, exitTime, type, 0, FINE_AMOUNT);
            }
        }
        else if (type == MOTORBIKE){
            if(motorbike_parking[v]->isVehicleFined()){
                return calculateFeeRecursive(entryTime, exitTime, type, 0, FINE_AMOUNT);
            }
        } else if(type == HANDICAPPED){
            if(handicapped_parking[v]->isVehicleFined()){
                return HANDICAPPED_FEE + FINE_AMOUNT;
            }
            return HANDICAPPED_FEE;
        }
        return calculateFeeRecursive(entryTime, exitTime, type, 0, 0);
    }


     int ParkingLot::calculateFeeRecursive(Time entryTime, Time exitTime, VehicleType type, int iter, int totalPrice){
        if(type == HANDICAPPED){
            return HANDICAPPED_FEE;
        }
        Time total_time_parked = exitTime - entryTime;
        if(total_time_parked.toHours() < 1) {
            return totalPrice + TypeToFee[type].first;
        }
        if(iter == MAX_PAYMENT_HOURS){
            return totalPrice;
        }
        iter += 1;
        totalPrice += TypeToFee[type].second;
        return calculateFeeRecursive(entryTime, exitTime.toHours() - 1, type, iter, totalPrice);
    }


    ParkingResult ParkingLot::exitParking(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time exitTime) {

        const Vehicle vehicle(licensePlate, ParkingSpot(), 0, CAR, false);
        unsigned int index;
        if(motorbike_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout, motorbike_parking[vehicle]->getType(), motorbike_parking[vehicle]->getLicensePlate(), motorbike_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout, motorbike_parking[vehicle]->vehicleGetParkingSpot(), exitTime, calculateFee(motorbike_parking[vehicle]->getEntryTime(), exitTime, MOTORBIKE, vehicle));//fee function
            motorbike_parking.remove(vehicle);
        }
        if(handicapped_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout, handicapped_parking[vehicle]->getType(), handicapped_parking[vehicle]->getLicensePlate(), handicapped_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout, handicapped_parking[vehicle]->vehicleGetParkingSpot(), exitTime, calculateFee(handicapped_parking[vehicle]->getEntryTime(), exitTime, HANDICAPPED, vehicle));//fee function
            handicapped_parking.remove(vehicle);
        }
        if(car_parking.getIndex(vehicle, index)){
            ParkingLotPrinter::printVehicle(std::cout, car_parking[vehicle]->getType(), car_parking[vehicle]->getLicensePlate(), car_parking[vehicle]->getEntryTime());
            ParkingLotPrinter::printExitSuccess(std::cout, car_parking[vehicle]->vehicleGetParkingSpot(), exitTime, calculateFee(car_parking[vehicle]->getEntryTime(), exitTime, CAR, vehicle));//fee function
            car_parking.remove(vehicle);
        }
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



//
//    static bool CompareParkingSpots(const Vehicle& v1, const Vehicle& v2){
//        return v2.spot < v1.spot;
//    }


    ostream& operator<<(ostream &os, const ParkingLot &parkingLot) {
        ParkingLotPrinter::printParkingLotTitle(os);
//        const vector<UniqueArray<Vehicle, Vehicle::compareVehicles>> LotVector = {parkingLot.motorbike_parking, parkingLot.handicapped_parking, parkingLot.car_parking};
//        sort(LotVector.begin(), LotVector.end(), CompareParkingSpots);
//        sort(parkingLot.car_parking.begin(), parkingLot.car_parking.end(), CompareParkingSpots);
//        for(auto* p :LotVector){
//            for(const auto& v : *p){
//                ParkingLotPrinter::printVehicle(os, v.)
//            }
//        }
        return os;
    }


    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        unsigned int count = 0;
        unsigned int idx;
        for(auto* p :{&motorbike_parking, &car_parking, &handicapped_parking}){
            for(const auto& v : *p){
                if(p->getIndex(v, idx)) {
                    if ((inspectionTime - v.getEntryTime()).toHours() >
                        MAX_TIME_ALLOWED_TO_PARK && !v.isVehicleFined()) {
                        v.setFine(true);
                        count++;
                    }
                }
            }
        }
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, count);
    }
}