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
        mutable bool fine;

        Vehicle(LicensePlate plate, ParkingSpot spot, Time entry_time = 0, VehicleType type = CAR, bool fine = false);
        Vehicle(const Vehicle& v);
        ~Vehicle() = default;
        Vehicle& operator=(const Vehicle&) = default;
        Time getEntryTime() const;
        VehicleType getType() const;
        LicensePlate getLicensePlate() const;
        ParkingSpot vehicleGetParkingSpot() const;
        bool isVehicleFined() const;
        void setFine(const bool fine) const;

        class compareVehicles{
        public:
            compareVehicles() = default;
            bool operator() (const Vehicle& v1, const Vehicle& v2){
                return (v1.licensePlate.compare(v2.licensePlate) == 0);
            }
        };
    };
}
#endif //EX3_MTM_VEHICLE_H
