#ifndef MTMPARKINGLOT_TIME_H
#define MTMPARKINGLOT_TIME_H

#include <iostream>

namespace ParkingLotUtils {

    using std::ostream;

    /**
     * @brief Represents a Time object that includes Day, Hour and Minute.
     * 
     */
    class Time {
    public:
    
        typedef unsigned int Day;
        typedef unsigned int Hour;
        typedef unsigned int Minute;

        /**
         * @brief Construct a new Time object
         * 
         * @param day The day of the time.
         * @param hour The hour of the time. Must be <= 24.
         * @param minute The minute of the time. Must be <= 60.
         * @throw std::invalid_argument in case of invalid arguments.
         */
        Time(Day day = 0, Hour hour = 0, Minute minute = 0);

        /**
         * @brief Adds the given number of minutes to this time object
         * 
         * @param minutes the number of minutes to add
         * @return Time& reference to this time object after the addition
         */
        Time& operator+=(const Minute minutes);

        /**
         * @brief Calculates the time difference between this and given Time object
         * 
         * @param time Time object to calculate time difference against
         * @return Time Time object representing the difference between this and given Time object (in absolute value)
         */
        Time operator-(const Time &time) const;

        /**
         * @brief Converts this to number of hours (rounded up)
         * 
         * @return Hour The amount of hours (rounded up) this Time object represents
         */
        Hour toHours() const;

        /**
         * @brief Print operator for Time object
         * 
         * @param os output stream to print into
         * @param time Time object to print
         * @return ostream& output stream after the print
         */
        friend ostream& operator<<(ostream &os, const Time &time);

    private:

        Day day;
        Hour hour;
        Minute minute;
    };

}

#endif //MTMPARKINGLOT_TIME_H
