#include <iostream>
#ifndef TIME
#define TIME
/// Time class for describing time
///
class Time
{
private:
    int h, m, s; /*!< variables for hour, minute and seconds */
    void substractInSeconds(const long int &s);
    void addInSeconds(const long long int &s);

public:
    /// struct for timezones support
    struct TimeZone
    {
        TimeZone(int h = 0, int m = 0)
        {
            this->h = h;
            this->m = m;
        }
        long int getTimeInSeconds() const
        {
            return (h * Time::MININHOUR + m) * Time::SECINMIN;
        }
        int m = 0;
        int h = 0;
    };

    /// static consts describing units of time
    static const int HOURSINDAY = 24;
    static const int MININHOUR = 60;
    static const int SECINMIN = 60;
    // -----------------
    /// Constructor for Time class
    /// @param h hour variable
    /// @param m minute variable
    /// @param s seconds variable
    Time(const int &h = 0, const int &m = 0, const int &s = 0);
    /// Add hour to current time
    /// @param h Number of hours to be added
    void addHours(const int &h);
    /// Add minute to current time
    /// @param m Number of minutes to be added
    void addMinutes(const int &m);
    /// Add seconds to current time
    /// @param s Number of seconds to be added
    void addSeconds(const long long int &s);
    /// Substract hours to current time
    /// @param h Number of hours to be substracted
    void substractHours(const int &h);
    /// Substract minutes to current time
    /// @param m Number of minutes to be substracted
    void substractMinutes(const int &m);
    /// Add seconds to current time
    /// @param s Number of seconds to be added
    void substractSeconds(const int &s);
    /// Set time by seconds
    /// @param s Number of seconds
    void setBySeconds(long long int s);
    /// Set minutes
    /// @param m Number of mintues
    void setMinute(const int &);
    /// Set hours
    /// @param h Number of hours
    void setHour(const int &);
    /// Set seconds
    /// @param s Number of seconds
    void setSecond(const int &);
    /// Set timezone
    /// @param tz Timezone
    void setTimeZone(const Time::TimeZone &tz);
    /// get time in seconds
    /// @return time in seconds
    long long int getTimeInSeconds() const;
    /// Adding operation
    Time operator+(const Time &t);
    /// Substracting operation
    Time operator-(const Time &t);

    /// reloading standart operators
    virtual void output(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Time &t);
    virtual void input(std::istream &in);
    friend std::istream &operator>>(std::istream &in, Time &t);

    /// Save time to file
    void saveToFile(const std::string &path);
    /// Read time to file
    void readFromFile(const std::string &path);

    ~Time();
};
#endif

#ifndef DATETIME
#define DATETIME
/// @brief Class for describing Date and time
/// @see Time
class DateTime : public Time
{
private:
    int y, m, d;
    bool numeric;

    // util functions
    void addInSeconds(const long long int &s);
    long long int getTimeInSeconds() const;
    void setBySeconds(const long long int &s);
    // -----------------------------------------
    void addInDays(const int &d);
    void substractInDays(const int &d);

public:
    /// Const for measuring time
    static const int DAYSINMONTH = 31;
    static const int MONTHINYEAR = 12;
    static const int SECINDAY = Time::HOURSINDAY * Time::MININHOUR * Time::SECINMIN;
    static const int DAYSINWEEK = 7;
    /// @brief  Constructor for DateTime class
    /// @param y years
    /// @param m minutes
    /// @param d days
    /// @param hh hours
    /// @param mm minutes
    /// @param ss seconds
    DateTime(const int &y = 0, const int &m = 1, const int &d = 1, const int &hh = 0, const int &mm = 0, const int &ss = 0);
    /// @brief Add days to date
    /// @param d number of days
    void addDays(const int &d);
    /// @brief Add years to date
    /// @param y number of years
    void addYears(const int &y);
    /// @brief Add months to date
    /// @param m number of months
    void addMonths(const int &m);
    /// @brief Sustract days from date
    /// @param d number of days
    void substractDays(const int &d);
    /// @brief Substract years from date
    /// @param y number of years
    void substractYears(const int &y);
    /// @brief Substract months from date
    /// @param n number of months
    void substractMonths(const int &n);
    /// @brief Set date by days 
    /// @param d number of days
    void setByDays(const int &d);
    /// @brief Get overall number of weeks in year
    /// @return number representing quantity of weeks
    int getNumberOfWeekInYear() const;
    int getNumberOfWeekInMonth() const;
    long int totalDays() const;

    /// @brief Change format of output to numeric
    void numericView();
    /// @brief Change format of output to string
    void stringView();

    /// reloading standart operators
    DateTime operator+(const DateTime &d);
    DateTime operator-(const DateTime &d);
    bool operator<(const DateTime &d);
    bool operator>(const DateTime &d);
    bool operator<=(const DateTime &d);
    bool operator>=(const DateTime &d);
    DateTime operator+(const Time &t);
    DateTime operator-(const Time &t);

    virtual void output(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const DateTime &d);
    virtual void input(std::istream &in);
    friend std::istream &operator>>(std::istream &inp, DateTime &d);

    // I/O in files
    void saveToFile(const std::string &path);
    void readFromFile(const std::string &path);
    ~DateTime();
};
#endif
