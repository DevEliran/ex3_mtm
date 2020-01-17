#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"
#include "Vehicle.h"

using namespace ParkingLotUtils;
using std::ostream;

namespace MtmParkingLot {


    class ParkingLot {
    public:

        UniqueArray<Vehicle, Vehicle::compareVehicles> motorbike_parking;
        UniqueArray<Vehicle, Vehicle::compareVehicles> car_parking;
        UniqueArray<Vehicle, Vehicle::compareVehicles> handicapped_parking;

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot() = default;
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        int calculateFee(Time entryTime, Time exitTime, VehicleType type, LicensePlate licensePlate);
        int calculateFeeRecursive(Time entryTime, Time exitTime, VehicleType type, int iter, int totalPrice);
        bool isVehicleInLot(LicensePlate licensePlate, VehicleType& type, unsigned int& index);
    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
