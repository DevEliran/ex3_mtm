#include "Time.h"
#include <iomanip>
#include <stdexcept>

using std::ostream;

namespace ParkingLotUtils {

    static const Time::Hour HOURS_PER_DAY = 24;
    static const Time::Minute MINUTES_PER_HOUR = 60;

    static Time::Minute toMinutes(Time::Day day, Time::Hour hour, Time::Minute minute) {
        return (day * HOURS_PER_DAY * MINUTES_PER_HOUR + hour * MINUTES_PER_HOUR + minute);
    }

    static Time fromMinutes(Time::Minute minutes) {
        Time::Hour hours = minutes / MINUTES_PER_HOUR;
        minutes = minutes % MINUTES_PER_HOUR;
        Time::Day days = hours / HOURS_PER_DAY;
        hours = hours % HOURS_PER_DAY;
        return Time(days, hours, minutes);
    }

    Time::Time(Time::Day day, Time::Hour hour, Time::Minute minute) : day(day), hour(hour), minute(minute) {
        if (hour > HOURS_PER_DAY || minute > MINUTES_PER_HOUR) {
            throw std::invalid_argument("Hour must be <= 24 and Minute must be <= 60");
        }
    }

    Time Time::operator-(const Time &time) const {
        Minute timeMinutes = toMinutes(time.day, time.hour, time.minute);
        Minute thisMinutes = toMinutes(this->day, this->hour, this->minute);
        if (thisMinutes < timeMinutes) {
            return fromMinutes(timeMinutes - thisMinutes);
        } else {
            return fromMinutes(thisMinutes - timeMinutes);
        }
    }

    Time& Time::operator+=(const Minute minutes) {
        Time newTime = fromMinutes(toMinutes(this->day, this->hour, this->minute) + minutes);
        (*this) = newTime;
        return (*this);
    }

    Time::Hour Time::toHours() const {
        return (this->day * HOURS_PER_DAY + this->hour + (this->minute > 0 ? 1 : 0));
    }

    ostream& operator<<(ostream &os, const Time &time) {
        return os << "Day " << time.day << ", " <<
                  std::setfill('0') << std::setw(2) << time.hour << ":" <<
                  std::setfill('0') << std::setw(2) << time.minute;
    }

}