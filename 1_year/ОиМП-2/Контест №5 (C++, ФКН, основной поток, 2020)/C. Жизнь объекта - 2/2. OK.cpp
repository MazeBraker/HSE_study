/// task N Семинар
#include <ctime>
#include <stdexcept>
#include <memory>
enum {
    SECONDS_IN_DAY = 86400
};

bool check2000(tm* old, tm* cur) {  // in ctime in feb 2020 - 28 days!!!!!!
    return (old->tm_year < 2000 || (old->tm_year == 2000 && old->tm_mon < 2)) &&
    (cur->tm_year > 2000 || (cur->tm_year == 2000 && cur->tm_mon >= 2));
}

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
        cur->tm_year = year;

        time_t new_dt = mktime(cur.get()) + delta * SECONDS_IN_DAY;
        tm* res = localtime(&new_dt);
        if (check2000(cur.get(), res)) {
            new_dt -= SECONDS_IN_DAY;
            res = localtime(&new_dt);
        } else if (check2000(res, cur.get())) {
            new_dt += SECONDS_IN_DAY;
            res = localtime(&new_dt);
        }
        return Date(res->tm_mday, res->tm_mon + 1, res->tm_year);
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
        cur->tm_year = year;

        std::unique_ptr<tm> second = std::make_unique<tm>();
        second->tm_mday = other.day;
        second->tm_mon = other.month - 1;
        second->tm_year = other.year;

        int res = difftime(mktime(cur.get()), mktime(second.get())) / SECONDS_IN_DAY;
        res -= check2000(cur.get(), second.get());
        res += check2000(second.get(), cur.get());

        return res;
    }
};