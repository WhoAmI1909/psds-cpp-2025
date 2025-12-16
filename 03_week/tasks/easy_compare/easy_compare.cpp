#include <stdexcept>
#include <map>

int markPriority(char mark) {
    static const std::map<char, int> priority = {
        {'Z', 0}, {'D', 1}, {'C', 2}, {'B', 3}, {'A', 4}
    };
    return priority.at(mark);
}

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const Date& lhs, const Date& rhs) {
     return std::tie(lhs.year, lhs.month, lhs.day) ==
            std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) <
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    if (markPriority(lhs.mark) != markPriority(rhs.mark)) {
        return markPriority(lhs.mark) < markPriority(rhs.mark);
    }
    if (lhs.score != rhs.score) {
        return lhs.score < rhs.score;
    }
    if (lhs.course != rhs.course) {
        return lhs.course > rhs.course;
    }
    return lhs.birth_date < rhs.birth_date;
}
