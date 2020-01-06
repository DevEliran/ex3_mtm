#include "ParkingSpot.h"

namespace ParkingLotUtils {

    ParkingSpot::ParkingSpot(VehicleType parkingBlock, unsigned int parkingNumber) : parkingBlock(parkingBlock), parkingNumber(parkingNumber) {}

    VehicleType ParkingSpot::getParkingBlock() const {
        return parkingBlock;
    }

    unsigned int ParkingSpot::getParkingNumber() const {
        return parkingNumber;
    }

    ostream& operator<< (ostream& os, const ParkingSpot& parkingSpot) {
        return os << vehicleTypeToString(parkingSpot.parkingBlock) << "-" << parkingSpot.parkingNumber;
    }

    bool operator < (const ParkingSpot& parkingSpot1, const ParkingSpot& parkingSpot2) {
        return   (parkingSpot1.parkingBlock <  parkingSpot2.parkingBlock) ||
                ((parkingSpot1.parkingBlock == parkingSpot2.parkingBlock) && (parkingSpot1.parkingNumber < parkingSpot2.parkingNumber));
    }

}