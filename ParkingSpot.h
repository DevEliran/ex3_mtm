#ifndef MTMPARKINGLOT_PARKINGSPOT_H
#define MTMPARKINGLOT_PARKINGSPOT_H

#include "ParkingLotTypes.h"
#include <iostream>

namespace ParkingLotUtils {

    using std::ostream;

    /**
     * @brief Represents a Parking Spot (Block + Number) of a Vehicle.
     * 
     */
    class ParkingSpot {
    public:
        
        /**
         * @brief Construct a new Parking Spot object
         * 
         * @param parkingBlock The Parking Block of the vehicle (represented by VehicleType enum)
         * @param parkingNumber The number of the parking spot within the block
         */
        ParkingSpot(VehicleType parkingBlock = FIRST, unsigned int parkingNumber = 0);

        /**
         * @brief Get the Parking Block of this ParkingSpot
         * 
         * @return VehicleType The Parking Block (represented by VehicleType enum)
         */
        VehicleType getParkingBlock() const;

        /**
         * @brief Get the Parking Number of this ParkingSpot
         * 
         * @return unsigned int The number of the parking spot within the block
         */
        unsigned int getParkingNumber() const;

        /**
         * @brief Compares given ParkingSpot objects
         * 
         * @param ps1
         * @param ps2 
         * @return true If ps1 < ps2
         * @return false otherwise
         */
        friend bool operator< (const ParkingSpot& ps1, const ParkingSpot& ps2);

        /**
         * @brief Prints given ParkingSpot object
         * 
         * @param os output stream to print into
         * @param parkingSpot ParkingSpot object to print
         * @return ostream& output stream after the print
         */
        friend ostream& operator<< (ostream& os, const ParkingSpot& parkingSpot);

    private:
        enum VehicleType parkingBlock;
        unsigned int parkingNumber;
    };

}

#endif //MTMPARKINGLOT_CAR_H
