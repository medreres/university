
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "datetime.hpp"
#include <stdexcept>
using std::cout;


Time::Time(const int &h, const int &m, const int &s)
{
    this->h = h;
    this->m = m;
    this->s = s;
}

void Time::addHours(const int &h)
{
    if (h < 0)
        throw std::invalid_argument("Can't add negative hours");

    this->addInSeconds(h * MININHOUR * SECINMIN);
}

void Time::addMinutes(const int &m)
{
    if (m < 0)
        throw std::invalid_argument("Can't add negative minutes");

    this->addInSeconds(m * SECINMIN);
}

void Time::addSeconds(const long long int &s)
{

    if (s < 0)
        throw std::invalid_argument("Can't add negative minutes");

    this->addInSeconds(s);
}

void Time::substractInSeconds(const long int &s)
{
    if (s > this->getTimeInSeconds())
        throw std::invalid_argument("Substracting results in negative time");

    long int result = this->getTimeInSeconds() - s;
    this->setBySeconds(result);
}

void Time::setBySeconds(long long int s)
{
    if (s < 0)
        s = Time::HOURSINDAY * Time::MININHOUR * Time::SECINMIN + s;
    int hoursInSeconds = s / (SECINMIN * MININHOUR);
    int minutesInSeconds = (s - hoursInSeconds * MININHOUR * SECINMIN) / (SECINMIN);
    int secondsLeftover = s - hoursInSeconds * MININHOUR * SECINMIN - minutesInSeconds * SECINMIN;
    this->s = secondsLeftover;
    this->m = minutesInSeconds;
    this->h = hoursInSeconds % HOURSINDAY;
}

long long int Time::getTimeInSeconds() const
{
    const int result = this->h * MININHOUR * SECINMIN + this->m * SECINMIN + this->s;
    return result;
}

void Time::addInSeconds(const long long int &s)
{
    long int result = this->getTimeInSeconds() + s;
    this->setBySeconds(result);
}
void Time::substractHours(const int &h)
{
    if (h < 0)
        throw std::invalid_argument("Can't substract negative hours");

    this->substractInSeconds(h * MININHOUR * SECINMIN);
}

void Time::substractMinutes(const int &m)
{
    if (m < 0)
        throw std::invalid_argument("Can't substract negative minutes");

    this->substractInSeconds(m * SECINMIN);
}

void Time::substractSeconds(const int &s)
{
    if (s < 0)
        throw std::invalid_argument("Can't substract negative seconds");

    this->substractInSeconds(s);
}

Time Time::operator+(const Time &t)
{
    Time result = *this;
    result.addInSeconds(t.h * MININHOUR * SECINMIN + t.m * SECINMIN + t.s);
    return result;
}

Time Time::operator-(const Time &t)
{
    Time result = *this;
    result.substractInSeconds(t.getTimeInSeconds());
    return result;
}

std::ostream &operator<<(std::ostream &out, const Time &t)
{
    t.output(out);
    return out;
}

void Time::output(std::ostream &out) const
{
    out << std::setfill('0') << std::setw(2) << this->h << ":";
    out << std::setfill('0') << std::setw(2) << this->m << ":";
    out << std::setfill('0') << std::setw(2) << this->s;
}

void Time::saveToFile(const std::string &path)
{
    using std::ofstream;
    ofstream out(path);
    if (!out)
        std::invalid_argument("Can't find file with such name");

    out << *this << std::endl;
    out.close();
}

//  ! (CRUTCH)? reloading operator >> using virtual methods to handle passing arguments by reference
std::istream &operator>>(std::istream &in, Time &t)
{
    t.input(in);
    return in;
}

void Time::input(std::istream &in)
{
    char ch;
    int h, m, s;
    in >> h >> ch >> m >> ch >> s;

    if (h > Time::HOURSINDAY || m > Time::MININHOUR || s > Time::SECINMIN)
        throw std::invalid_argument("Error. Invalid arguments while reading from file.");
    this->setBySeconds((h * Time::MININHOUR + m) * Time::SECINMIN + s);
}

void Time::readFromFile(const std::string &path)
{
    using std::ifstream;
    ifstream inp(path);
    if (!inp)
        std::invalid_argument("Can't find file");

    inp >> *this;

    inp.close();
}

void Time::setMinute(const int &m)
{
    if (m < 0)
        throw std::invalid_argument("Can't set negative value to time");
    this->m = m;
}
void Time::setHour(const int &h)
{
    if (h < 0)
        throw std::invalid_argument("Can't set negative value to time");

    this->h = h;
}
void Time::setSecond(const int &s)
{
    if (s < 0)
        throw std::invalid_argument("Can't set negative value to time");

    this->s = s;
}
Time::~Time()
{
}

// DATETIME METHODS
const std::string Days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const std::string Months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// DateTime::DateTime(const int &y, const int &m, const int &d, const Time &t) : Time(t)
// {
//     if (!m || !d)
//         throw std::invalid_argument("Can't set day/month to zero");
//     this->y = y;
//     this->m = m;
//     this->d = d;
//     this->numeric = true;
// }

DateTime::DateTime(const int &y, const int &m, const int &d, const int &hh, const int &mm, const int &ss) : Time(hh, mm, ss)
{
    if (!m || !d)
        throw std::invalid_argument("Can't set day/month to zero");
    this->y = y;
    this->m = m;
    this->d = d;
    this->numeric = true;
}
DateTime::~DateTime()
{
}

void Time::setTimeZone(const TimeZone &tz)
{
    long long int totalSec = this->getTimeInSeconds() + tz.getTimeInSeconds();
    this->setBySeconds(totalSec);
}

long long int DateTime::getTimeInSeconds() const
{
    long long int result = (*this).Time::getTimeInSeconds() + ((this->y * DAYSINMONTH * MONTHINYEAR) + (this->m * DAYSINMONTH) + this->d) * SECINDAY;
    return result;
}

void DateTime::addInSeconds(const long long int &s)
{
    long long int result = this->getTimeInSeconds() + s;
    this->setBySeconds(result);
}

void DateTime::setBySeconds(const long long int &s)
{
    if (s < 0)
        throw std::invalid_argument("Can't set time to negative");
    int hoursInSeconds = s / (SECINMIN * MININHOUR);
    int minutesInSeconds = (s - hoursInSeconds * MININHOUR * SECINMIN) / (SECINMIN);
    int secondsLeftover = s - hoursInSeconds * MININHOUR * SECINMIN - minutesInSeconds * SECINMIN;
    this->setSecond(secondsLeftover);
    this->setMinute(minutesInSeconds);
    if (hoursInSeconds / HOURSINDAY)
    {
        this->d++;
    }
    this->setHour(hoursInSeconds % HOURSINDAY);
}

long int DateTime::totalDays() const
{
    long int result = (this->y * MONTHINYEAR + (this->m - 1)) * DAYSINMONTH + this->d;
    return result;
}

void DateTime::addInDays(const int &d)
{
    if (d < 0)
        throw std::invalid_argument("Can't add negative value");

    long int result = this->totalDays() + d;
    this->setByDays(result);
}
void DateTime::setByDays(const int &d)
{
    if (d < 0)
        throw std::invalid_argument("Negative time.");
    this->y = d / (MONTHINYEAR * DAYSINMONTH);
    this->m = (d - (this->y * (MONTHINYEAR * DAYSINMONTH))) / (DAYSINMONTH);
    this->m = (this->m) ? this->m : 1;
    this->d = (d % DAYSINMONTH) ? (d % DAYSINMONTH) : 1;
}

void DateTime::addDays(const int &d)
{
    this->addInDays(d);
}

void DateTime::addYears(const int &y)
{
    this->addInDays(y * MONTHINYEAR * DAYSINMONTH);
}

void DateTime::addMonths(const int &m)
{
    this->addInDays(m * DAYSINMONTH);
}

void DateTime::substractDays(const int &d)
{
    int result = this->totalDays() - d;
    setByDays(result);
}

void DateTime::substractYears(const int &y)
{
    this->setByDays(y * MONTHINYEAR * DAYSINMONTH);
}

void DateTime::substractMonths(const int &m)
{
    this->setByDays(m * DAYSINMONTH);
}

DateTime DateTime::operator+(const DateTime &d)
{
    DateTime result = *this;
    long int timeInSec = ((const Time &)(*this)).getTimeInSeconds() + ((const Time &)(d)).getTimeInSeconds();
    result.setBySeconds(timeInSec);
    result.setByDays(d.totalDays() + result.totalDays());
    return result;
}

DateTime DateTime::operator-(const DateTime &d)
{
    DateTime result = *this;
    result.setByDays(this->totalDays() - d.totalDays());
    return result;
}

bool DateTime::operator<(const DateTime &d)
{
    if (this->y < d.y)
        return true;
    else if (this->y == d.y)
    {
        if (this->m < d.m)
            return true;
        else if (this->m == d.m)
        {
            if (this->d < d.d)
                return true;
        }
    }
    return false;
}
bool DateTime::operator>(const DateTime &d)
{
    if (this->y > d.y)
        return true;
    else if (this->y == d.y)
    {
        if (this->m > d.m)
            return true;
        else if (this->m == d.m)
        {
            if (this->d > d.d)
                return true;
        }
    }
    return false;
}
bool DateTime::operator<=(const DateTime &d)
{
    if (this->y < d.y)
        return true;
    else if (this->y == d.y)
    {
        if (this->m < d.m)
            return true;
        else if (this->m == d.m)
        {
            if (this->d <= d.d)
                return true;
        }
    }
    return false;
}
bool DateTime::operator>=(const DateTime &d)
{
    if (this->y > d.y)
        return true;
    else if (this->y == d.y)
    {
        if (this->m > d.m)
            return true;
        else if (this->m == d.m)
        {
            if (this->d >= d.d)
                return true;
        }
    }
    return false;
}
void DateTime::numericView()
{
    this->numeric = true;
}

void DateTime::stringView()
{
    this->numeric = false;
}

DateTime DateTime::operator+(const Time &t)
{
    DateTime result;
    // if after adding times the are one another day, count it, otherwise set days to zero
    result.d = 0;
    result.setBySeconds(((const Time &)(*this)).getTimeInSeconds() + ((const Time &)(t)).getTimeInSeconds());
    result.setByDays(result.totalDays() + this->totalDays());
    return result;
}

DateTime DateTime::operator-(const Time &t)
{
    DateTime result;
    result.setBySeconds(((const Time &)(*this)).getTimeInSeconds() - ((const Time &)(t)).getTimeInSeconds());
    result.setByDays(result.totalDays() + this->totalDays());
    return result;
}

int DateTime::getNumberOfWeekInYear() const
{
    int totalDays = this->totalDays();
    return totalDays / DateTime::DAYSINWEEK;
}

int DateTime::getNumberOfWeekInMonth() const
{
    int numberOfWeek = this->d / DateTime::DAYSINWEEK;
    return (numberOfWeek) ? numberOfWeek : 1;
}

std::ostream &operator<<(std::ostream &out, const DateTime &d)
{
    d.output(out);
    return out;
}
void DateTime::output(std::ostream &out) const
{
    if (this->numeric)
    {
        out << this->y << ",";
        out << std::setfill('0') << std::setw(2) << this->m << ",";
        out << std::setfill('0') << std::setw(2) << this->d << " ";
    }
    else
    {
        out << this->y << ", ";
        out << Months[this->m - 1] << ", ";
        out << Days[(this->d - 1) % 7] << " ";
    }
    (*this).Time::output(out);
}

std::istream &operator>>(std::istream &inp, DateTime &d)
{
    d.input(inp);
    d.Time::input(inp);
    return inp;
}

void DateTime::input(std::istream &in)
{
    char ch;
    int y, m, d;
    in >> y >> ch >> m >> ch >> d;

    if (m > DateTime::MONTHINYEAR || d > DateTime::DAYSINMONTH)
        throw std::invalid_argument("Error. Invalid arguments for month/day while reading from file");

    this->setByDays((y * DateTime::MONTHINYEAR + m) * DAYSINMONTH + d);
}

void DateTime::saveToFile(const std::string &path)
{
    using std::ofstream;
    ofstream out(path);
    if (!out)
        std::invalid_argument("Can't find file with such name");

    out << *this << std::endl;
    out << (Time &)(*this) << std::endl;
    out.close();
}

void DateTime::readFromFile(const std::string &path)
{
    using std::ifstream;
    ifstream inp(path);
    if (!inp)
        std::invalid_argument("Can't find file");

    inp >> *this;

    inp.close();
}
