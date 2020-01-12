#include "Vehicle.h"

using namespace ParkingLotUtils;
using namespace std;

namespace MtmParkingLot {

    Vehicle::Vehicle(LicensePlate plate, Time entry_time, VehicleType type,
                     ParkingSpot spot):licensePlate(plate), entryTime(entry_time), type(type), spot(spot) {
    }


    ParkingSpot Vehicle::getParkingSpot(MtmParkingLot::Vehicle v) {
        return v.spot;
    }


    Time Vehicle::getEntryTime(MtmParkingLot::Vehicle v) {
        return v.entryTime;
    }


    LicensePlate Vehicle::getLicensePlate(MtmParkingLot::Vehicle v) {
        return licensePlate;
    }


    VehicleType Vehicle::getType(MtmParkingLot::Vehicle v) {
        return v.type;
    }


    class compareVehicles {
    public:
        compareVehicles() = default;
        bool operator() (LicensePlate lp1, LicensePlate lp2) const {
            return (lp1.compare(lp2) == 0);
        };
    };
}
