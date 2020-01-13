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
        bool fine;

        Vehicle(LicensePlate plate, ParkingSpot spot, Time entry_time = 0, VehicleType type = CAR, bool fine = false);
        ~Vehicle();
        Time getEntryTime() const;
        VehicleType getType() const;
        LicensePlate getLicensePlate() const;
        ParkingSpot vehicleGetParkingSpot() const;
        bool isVehicleFined() const;

        class compareVehicles{};
    };
}
#endif //EX3_MTM_VEHICLE_H
