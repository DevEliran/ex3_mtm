#ifndef MTMPARKINGLOT_PARKINGLOTPRINTER_H
#define MTMPARKINGLOT_PARKINGLOTPRINTER_H

#include "Time.h"
#include "ParkingSpot.h"
#include "ParkingLotTypes.h"
#include <iostream>

using std::ostream;
using std::type_info;

namespace ParkingLotUtils {

    class ParkingLotPrinter {
    public:
        
        /**
         * @brief Prints the Vehicle details according to the required format.
         * 
         * @param os output stream to print into
         * @param vehicleType Type of the vehicle (Motorbike/Car/Handicapped)
         * @param licensePlate License plate of the vehicle
         * @param entranceTime entrance time of the vehicle
         * @return ostream& output stream after the print
         */
        static ostream& printVehicle(ostream& os, VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);

        /**
         * @brief Prints the successful entry of a Vehicle into the ParkingLot
         * 
         * @param os output stream to print into
         * @param parkingSpot The Parking Spot acquired by the Vehicle
         * @return ostream& output stream after the print
         */
        static ostream& printEntrySuccess(ostream& os, ParkingSpot parkingSpot);

        /**
         * @brief Prints unsuccessful entry of a Vehicle, due to no available parking spot
         * 
         * @param os output stream to print into
         * @return ostream& output stream after the print
         */
        static ostream& printEntryFailureNoSpot(ostream& os);

        /**
         * @brief Prints unsuccessful entry of a Vehicle, due to Vehicle already parked
         * 
         * @param os output stream to print into
         * @param parkingSpot The actual parking spot of the vehicle
         * @return ostream& output stream after the print
         */
        static ostream& printEntryFailureAlreadyParked(ostream& os, ParkingSpot parkingSpot);

        /**
         * @brief Prints successful exit of a Vehicle from the Parking lot
         * 
         * @param os output stream to print into
         * @param parkingSpot The Parking Spot where the vehicle was parked
         * @param exitTime The exit time
         * @param price The total price the vehicle has to pay (including fines)
         * @return ostream& output stream after the print
         */
        static ostream& printExitSuccess(ostream& os, ParkingSpot parkingSpot, Time exitTime, unsigned int price);

        /**
         * @brief Prints unsuccessful exit of a Vehicle from the Parking lot
         * 
         * @param os output stream to print into
         * @param licensePlate The license plate of the vehicle
         * @return ostream& output stream after the print
         */
        static ostream& printExitFailure(ostream& os, LicensePlate licensePlate);

        /**
         * @brief Prints the result of an inspection on the Parking lot
         * 
         * @param os output stream to print into
         * @param inspectionTime The time of the inspection
         * @param numFined Total number of vehicles fined during the inspection
         * @return ostream& output stream after the print
         */
        static ostream& printInspectionResult(ostream& os, Time inspectionTime, unsigned int numFined);

        /**
         * @brief Prints the title for ParkingLot print operation
         * 
         * @param os output stream to print into
         * @return ostream& output stream after the print
         */
        static ostream& printParkingLotTitle(ostream& os);

        /**
         * @brief Prints the parking spot of the vehicle
         * 
         * @param os output stream to print into
         * @param parkingSpot The parking spot of the vehicle to print
         * @return ostream& output stream after the print
         */
        static ostream& printParkingSpot(ostream& os, ParkingSpot parkingSpot);


    private:
        ParkingLotPrinter() = default;
    };

}
#endif //MTMPARKINGLOT_PARKINGLOTPRINTER_H
