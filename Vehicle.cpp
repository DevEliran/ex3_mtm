#include "Vehicle.h"

using namespace ParkingLotUtils;
using namespace std;

namespace MtmParkingLot {

    Vehicle::Vehicle(LicensePlate plate, ParkingSpot spot, Time entry_time,
                        VehicleType type, bool fine):licensePlate(plate), entryTime(entry_time), type(type), spot(spot), fine(fine) {
    }

    Vehicle::Vehicle(const Vehicle &v):licensePlate(v.licensePlate),entryTime(v.entryTime), type(v.type), spot(v.spot), fine(v.fine){
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


    void Vehicle::setFineTrue() const {
        this->fine = true;
    }

}
