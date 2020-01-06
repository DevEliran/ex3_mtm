#include "ParkingLotPrinter.h"
#include <iostream>
#include <cassert>

namespace ParkingLotUtils {

    using std::endl;

    static ostream& printParkingSpotNoEndl(ostream& os, ParkingSpot parkingSpot) {
        return os << ", parked in: " << parkingSpot;
    }

    ostream& ParkingLotPrinter::printVehicle(ostream &os, VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
        return os << "Vehicle Type: " << vehicleTypeToString(vehicleType) << ", License Plate: " << licensePlate << ", arrived on: " << entranceTime;
    }

    ostream& ParkingLotPrinter::printEntrySuccess(ostream& os, ParkingSpot parkingSpot) {
        os << " has successfully entered the Parking Lot";
        return printParkingSpot(os, parkingSpot);
    }

    ostream& ParkingLotPrinter::printEntryFailureNoSpot(ostream& os) {
        return os << " failed entering Parking Lot : no available parking spot!" << endl;
    }

    ostream& ParkingLotPrinter::printEntryFailureAlreadyParked(ostream& os, ParkingSpot parkingSpot) {
        os << " is already in the Parking Lot";
        return printParkingSpot(os, parkingSpot);
    }

    ostream& ParkingLotPrinter::printExitSuccess(ostream& os, ParkingSpot parkingSpot, Time exitTime, unsigned int price) {
        printParkingSpotNoEndl(os, parkingSpot);
        return os << " has exited Parking Lot on: " << exitTime << ", Total price to pay: " << price << endl;
    }

    ostream& ParkingLotPrinter::printExitFailure(ostream& os, LicensePlate licensePlate) {
        return os << "Error: Vehicle with License Plate: " << licensePlate << " not found!" << endl;
    }

    ostream& ParkingLotPrinter::printInspectionResult(ostream& os, Time inspectionTime, unsigned int numFined) {
        return os << "Parking lot was inspected on: " << inspectionTime << ". Total of " << numFined << " vehicles were fined." << endl;
    }

    ostream& ParkingLotPrinter::printParkingLotTitle(ostream& os) {
        os << "=============" << endl;
        os << "MtmParkingLot" << endl;
        os << "=============" << endl;
        return os;
    }

    ostream& ParkingLotPrinter::printParkingSpot(ostream& os, ParkingSpot parkingSpot) {
        printParkingSpotNoEndl(os, parkingSpot);
        return os << endl;
    }

}