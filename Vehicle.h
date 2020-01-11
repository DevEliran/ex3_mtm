#ifndef EX3_MTM_VEHICLE_H
#define EX3_MTM_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"
using namespace ParkingLotUtils;

class Vehicle {
    LicensePlate licensePlate;
    Time entryTime;
    VehicleType type;
public:
    Vehicle(LicensePlate plate, Time entry_time, VehicleType type):
    licensePlate(plate), entryTime(entry_time), type(type){
    }

    getEntryTime(Vehicle v){
        return entryTime;
    }

    getType(Vehicle v){
        return type;
    }

    getLicensePlate(Vehicle v){
        return licensePlate;
    }
};
#endif //EX3_MTM_VEHICLE_H
