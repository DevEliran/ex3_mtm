#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
        UniqueArray motorbike_parking;
        UniqueArray car_parking;
        UniqueArray handicapped_parking;
    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };
    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]):
    motorbike_parking(new UniqueArray(parkingBlockSizes[0])), car_parking(new UniqueArray(parkingBlockSizes[2])), handicapped_parking(new UniqueArray(parkingBlockSizes[1])){
    }


    ParkingLot::~ParkingLot() {
        delete[] motorbike_parking;
        delete[] car_parking;
        delete[] handicapped_parking;
    }


    ParkingResult ParkingLot::enterParking(
            ParkingLotUtils::VehicleType vehicleType,
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time entranceTime) {
        int entered_successfully = -1;
        unsigned int index;// should be a refrence
        if (vehicleType == 0){
            if(motorbike_parking.getIndex(licensePlate, index)){
                //print according to 3.c
                return VEHICLE_ALREADY_PARKED;
            }
            entered_successfully = motorbike_parking.insert(licensePlate);
            catch (motorbike_parking::UniqueArrayIsFullException& e) {
                //print according to 3.b
                return NO_EMPTY_SPOT;
            }
        } else if (vehicleType == 1){
            if (handicapped_parking.getIndex(licensePlate, index)){
                //print according to 3.c
                return VEHICLE_ALREADY_PARKED
            }
            entered_successfully = handicapped_parking.insert(licensePlate);
            catch (handicapped_parking::UniqueArrayIsFullException& e) {
                //print according to 3.b
                return NO_EMPTY_SPOT;
            }
        } else if (vehicleType == 2){
            if (car_parking.getIndex(licensePlate, index)){
                //print according to 3.c
                return VEHICLE_ALREADY_PARKED;
            }
            entered_successfully = car_parking.insert(licensePlate);
            catch (car_parking::UniqueArrayIsFullException& e) {
                //print according to 3.b
                return NO_EMPTY_SPOT;
            }
        }
        if (entered_successfully > -1){
            //print according to 3.a
            return SUCCESS;
        }
    }


    ParkingResult ParkingLot::exitParking(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time exitTime) {
        unsigned int index1, index2, index3;//should be refrences to -1
        if(!motorbike_parking.getIndex(licensePlate, index1) &&
            !handicapped_parking.getIndex(licensePlate, index2)&&
            !car_parking.getIndex(licensePlate, index3)){
            //print according to 4.b
            return VEHICLE_NOT_FOUND;
        }
        //print according to 4.a
        return SUCCESS; // should be parking_success according to docs - > not found
    }


    ParkingResult ParkingLot::getParkingSpot(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::ParkingSpot &parkingSpot) const {

    }
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
