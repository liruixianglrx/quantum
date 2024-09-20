#ifndef DATETIME_H
#define DATETIME_H

#include <string>

class DateTime {
public:
    // Constructor
    DateTime(){};
    DateTime(const std::string& dateStr);
    DateTime(int y, int m, int d);

    // Convert the date to a string in the format YYYY-MM-DD
    std::string toString() const;

    // Static function to get the date `days` days before the given `date`
    // days can be negatives
    static DateTime daysBefore(const DateTime& date, int days);

    // Calculate the number of days between this date and another date
    int daysBetween(const DateTime& other) const;

private:
    int m_year, m_month, m_day;

    // Check if the date is valid
    bool isValidDate() const;

    // Static function to get the number of days in a given month
    static int daysInMonth(int y, int m);

    // Static function to check if a year is a leap year
    static bool isLeapYear(int y);

    // Calculate the total number of days from 2000 to this date
    int daysFromYear2000() const;
};

#endif // DATETIME_H
