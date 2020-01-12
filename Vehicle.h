#ifndef EX3_MTM_VEHICLE_H
#define EX3_MTM_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"

using namespace ParkingLotUtils;
namespace MtmParkingLot {
    class Vehicle {
    public:

        LicensePlate licensePlate;
        Time entryTime;
        VehicleType type;
        ParkingSpot spot;

        Vehicle(LicensePlate plate, Time entry_time, VehicleType type,
                ParkingSpot spot);
        Time getEntryTime(Vehicle v);
        VehicleType getType(Vehicle v);
        LicensePlate getLicensePlate(Vehicle v);
        ParkingSpot getParkingSpot(Vehicle v);
//        bool compareVehicles(LicensePlate lp1, LicensePlate lp2);
        class compareVehicles{};
    };
}
#endif //EX3_MTM_VEHICLE_H
