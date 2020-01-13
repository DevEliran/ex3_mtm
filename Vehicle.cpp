#include "Vehicle.h"

using namespace ParkingLotUtils;
using namespace std;

namespace MtmParkingLot {

    Vehicle::Vehicle(LicensePlate plate, ParkingSpot spot, Time entry_time,
                        VehicleType type, bool fine):licensePlate(plate), entryTime(entry_time), type(type), spot(spot), fine(fine) {
    }


    ParkingSpot Vehicle::vehicleGetParkingSpot() const{
        return spot;
    }


    Time Vehicle::getEntryTime() const{
        return entryTime;
    }


    LicensePlate Vehicle::getLicensePlate() const{
        return licensePlate;
    }


    VehicleType Vehicle::getType() const{
        return type;
    }


    bool Vehicle::isVehicleFined() const {
        return fine;
    }

    class compareVehicles {
    public:
        compareVehicles() = default;
        bool operator() (const Vehicle& v1, const Vehicle& v2){
            return (v1.licensePlate.compare(v2.licensePlate) == 0);
        }
    };
}
