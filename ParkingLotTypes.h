#ifndef MTMPARKINGLOT_PARKINGLOTTYPES_H
#define MTMPARKINGLOT_PARKINGLOTTYPES_H

#include <string>

using std::string;

namespace ParkingLotUtils {

    typedef string LicensePlate;

    enum ParkingResult {
        SUCCESS,
        NO_EMPTY_SPOT,
        VEHICLE_NOT_FOUND,
        VEHICLE_ALREADY_PARKED
    };

    enum VehicleType {
        MOTORBIKE = 0,
        HANDICAPPED,
        CAR,


        FIRST = MOTORBIKE,
        LAST = CAR
    };

    /**
     * @brief Converts given VehicleType to string
     * 
     * @param vehicleType VehicleType to convert to string
     * @return string corresponding to the VehicleType
     */
    inline string vehicleTypeToString(VehicleType vehicleType) {
        static const string vehicleTypeNames[VehicleType::LAST-VehicleType::FIRST+1] = {"Motorbike", "Handicapped", "Car"};
        return vehicleTypeNames[vehicleType];
    }

}

#endif //MTMPARKINGLOT_PARKINGLOTTYPES_H
