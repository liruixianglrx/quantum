#include "DateTime.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

DateTime::DateTime(const std::string& dateStr) {
    std::istringstream iss(dateStr);
    char dash1, dash2;
    if (!(iss >> m_year >> dash1 >> m_month >> dash2 >> m_day) || dash1 != '-' || dash2 != '-' || !isValidDate()) {
        throw std::invalid_argument("Invalid date format. Expected format is YYYY-MM-DD.");
    }
}

std::string DateTime::toString() const {
    std::ostringstream oss;
    oss << m_year << '-' << std::setfill('0') << std::setw(2) << m_month << '-' << std::setw(2) << m_day;
    return oss.str();
}

DateTime DateTime::daysBefore(const DateTime& date, int days) {
    int y = date.m_year;
    int m = date.m_month;
    int d = date.m_day;

    // Adjust based on whether days is positive or negative
    if (days > 0) {
        while (days > 0) {
            if (d > days) {
                d -= days;
                days = 0;
            } else {
                days -= d;
                --m;
                if (m == 0) {
                    --y;
                    m = 12;
                }
                d = daysInMonth(y, m);
            }
        }
    } else if (days < 0) {
        days = -days; // Convert days to positive for the loop
        while (days > 0) {
            int daysLeftInMonth = daysInMonth(y, m) - d;
            if (daysLeftInMonth >= days) {
                d += days;
                days = 0;
            } else {
                days -= daysLeftInMonth + 1;
                d = 1;
                ++m;
                if (m > 12) {
                    ++y;
                    m = 1;
                }
            }
        }
    }

    return DateTime(y, m, d);
}

DateTime::DateTime(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {}

bool DateTime::isValidDate() const {
    return m_month >= 1 && m_month <= 12 && m_day >= 1 && m_day <= daysInMonth(m_year, m_month);
}

int DateTime::daysInMonth(int y, int m) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (isLeapYear(y) ? 29 : 28);
        default: return 0;
    }
}

bool DateTime::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::daysFromYear2000() const {
    int days = 0;
    // Calculate days from 2000 to the start of this year
    for (int y = 2000; y < m_year; ++y) {
        days += (isLeapYear(y) ? 366 : 365);
    }
    // Calculate days from the start of this year to the start of this month
    for (int m = 1; m < m_month; ++m) {
        days += daysInMonth(m_year, m);
    }
    // Calculate days from the start of this month to this day
    days += m_day - 1;  // Subtract 1 because we count the full days before the current day
    return days;
}

int DateTime::daysBetween(const DateTime& other) const {
    return std::abs(daysFromYear2000() - other.daysFromYear2000());
}
