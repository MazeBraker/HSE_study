#include <ctime>
#include <stdexcept>
#include <memory>
enum {
    SECONDS_IN_DAY = 86400
};

class Date {
private:
    int day, month, year;

public:
    Date(int d, int m, int y): day(d), month(m), year(y) {
        if (y < 1970 || y > 2099 || m < 1 || m > 12 || d < 1 || d > 31) {
            throw std::invalid_argument("Invalid date");
        }
    }

    Date operator=(const Date& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        return *this;
    }

    int GetDay() const {
        return day;
    }

    int GetMonth() const {
        return month;
    }

    int GetYear() const {
        return year;
    }

    bool operator<(const Date& other) {
        if (year < other.year || year == other.year && month < other.month) {
            return true;
        }
        return year == other.year && month == other.month && day < other.day;
    }

    Date operator+(int delta) {
        std::unique_ptr<tm> cur = std::make_unique<tm>();
        cur->tm_mday = day;
        cur->tm_mon = month - 1;
        cur->tm_year = year - 1900;

        time_t new_dt = mktime(cur.get()) + delta * SECONDS_IN_DAY;
        tm* res = localtime(&new_dt);
        return Date(res->tm_mday, res->tm_mon + 1, res->tm_year + 1900);
    }

    Date operator-(int delta) {
        return *this + (-delta);
    }
    Date operator++() {
        *this = *this + 1;
        return *this;
    }
    Date operator--() {
        *this = *this - 1;
        return *this;
    }

    int operator-(const Date& other) {
        std::unique_ptr<tm> cur = std::make_unique<tm>();
        cur->tm_mday = day;
        cur->tm_mon = month - 1;
        cur->tm_year = year - 1900;

        std::unique_ptr<tm> second = std::make_unique<tm>();
        second->tm_mday = other.day;
        second->tm_mon = other.month - 1;
        second->tm_year = other.year - 1900;

        return difftime(mktime(cur.get()), mktime(second.get())) / SECONDS_IN_DAY;
    }
};