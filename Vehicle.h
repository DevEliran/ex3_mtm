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


        /**
         * @brief Constructor for Vehicle Object.
         * @param entry_time
         * @param fine
         * @param plate
         * @param spot
         * @param type
         */
        Vehicle(LicensePlate plate, ParkingSpot spot, Time entry_time = 0,
                VehicleType type = CAR, bool fine = false);


        /**
         * @brief Copy Constructor for Vehicle Object.
         * @param v - Vehicle object to copy.
         */
        Vehicle(const Vehicle& v);


        /**
         * Default destructor.
         */
        ~Vehicle() = default;


        /**
         * Default operator=.
         */
        Vehicle& operator=(const Vehicle&) = default;


        /**
         * @return entryTime of a Vehicle object.
         */
        Time getEntryTime() const;


        /**
         * @return type of a Vehicle object.
         */
        VehicleType getType() const;


        /**
         * @return licensePlate of a Vehicle object.
         */
        LicensePlate getLicensePlate() const;


        /**
         * @return ParkingSpot of a Vehicle object.
         */
        ParkingSpot vehicleGetParkingSpot() const;


        /**
         * @return true if the Vehicle is fined.
         * @return false otherwise
         */
        bool isVehicleFined() const;


        /**
         * Sets the fine attribute of this Vehicle object to 'true'.
         */
        void setFineTrue() const;

        class compareVehicles{
        public:
            compareVehicles() = default;


            /**
             * @brief Comparing Vehicles by their licensePlate.
             * @param v1
             * @param v2
             * @return true if both Vehicles have the same licensePlate.
             * @return false otherwise.
             */
            bool operator() (const Vehicle& v1, const Vehicle& v2){
                return (v1.licensePlate.compare(v2.licensePlate) == 0);
            }
        };
    };
}
#endif //EX3_MTM_VEHICLE_H
