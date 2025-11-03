#include "Sign.h"
#include <iostream>

using namespace Signs;

void Sign::setZodiac(int birthday[3]) {

    int day = birthday[0];
    int month = birthday[1];

    if      ((month ==  3 && day >= 21) || (month ==  4 && day <= 19))
        zodiac = Zodiac::Aries;

    else if ((month ==  4 && day >= 20) || (month ==  5 && day <= 20))
        zodiac = Zodiac::Taurus;
    
    else if ((month ==  5 && day >= 21) || (month ==  6 && day <= 20))
        zodiac = Zodiac::Gemini;
    
    else if ((month ==  6 && day >= 21) || (month ==  7 && day <= 22))
        zodiac = Zodiac::Cancer;
    
    else if ((month ==  7 && day >= 23) || (month ==  8 && day <= 22))
        zodiac = Zodiac::Leo;
    
    else if ((month ==  8 && day >= 23) || (month ==  9 && day <= 22))
        zodiac = Zodiac::Virgo;
    
    else if ((month ==  9 && day >= 23) || (month == 10 && day <= 22))
        zodiac = Zodiac::Libra;
    
    else if ((month == 10 && day >= 23) || (month == 11 && day <= 21))
        zodiac = Zodiac::Scorpio;
    
    else if ((month == 11 && day >= 22) || (month == 12 && day <= 21))
        zodiac = Zodiac::Sagittarius;
    
    else if ((month == 12 && day >= 22) || (month ==  1 && day <= 19))
        zodiac = Zodiac::Capricorn;
    
    else if ((month ==  1 && day >= 20) || (month ==  2 && day <= 18))
        zodiac = Zodiac::Aquarius;
    
    else if ((month ==  2 && day >= 19) || (month ==  3 && day <= 20))
        zodiac = Zodiac::Pisces;
    
    else
        zodiac = Zodiac::Capricorn;
}

bool Sign::validateAndSetBirthday(int birthday[3]) {

    int day = birthday[0];
    int month = birthday[1];
    int year = birthday[2];

    if (day < 1 || month < 1 || month > 12 || year < 1900)
        return false;
                        // 1   2   3   4   5   6   7   8   9  10  11  12
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) )
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        return false;

    this->birthday[0] = day;
    this->birthday[1] = month;
    this->birthday[2] = year;

    setZodiac(this->birthday);

    return true;
}

std::string Sign::trim(const std::string& str)   {

    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);

    return trimmed;
}

Sign::Sign() : name("unknown"), lastName("unknown"), zodiac(Zodiac::Capricorn) {

    birthday[0] = 1;
    birthday[1] = 1;
    birthday[2] = 1900;
}

Sign::Sign(const std::string& name, const std::string& lastName, int birthday[3]) : name(name), lastName(lastName) {

    if (!validateAndSetBirthday(birthday)) {
        this->birthday[0] = DEFAULT_BIRTHDAY[0];
        this->birthday[1] = DEFAULT_BIRTHDAY[1];
        this->birthday[2] = DEFAULT_BIRTHDAY[2];
        zodiac = Zodiac::Capricorn;

        std::cout << "Error reading birthday. Default set to 01-01-1900" << std::endl;
    }
}

Sign::Sign(const Sign& other) {

    name = other.name;
    lastName = other.lastName;
    birthday[0] = other.birthday[0];
    birthday[1] = other.birthday[1];
    birthday[2] = other.birthday[2];
    zodiac = other.zodiac;
}

Sign& Sign::operator =(const Sign& other) {

    if (this == &other)
        return *this;

    name = other.name;
    lastName = other.lastName;
    birthday[0] = other.birthday[0];
    birthday[1] = other.birthday[1];
    birthday[2] = other.birthday[2];
    zodiac = other.zodiac;

    return *this;
}

bool Sign::operator ==(const Sign& other) const {

    if (this == &other)
        return true;

    return name == other.name &&
        lastName == other.lastName &&
        birthday[0] == other.birthday[0] &&
        birthday[1] == other.birthday[1] &&
        birthday[2] == other.birthday[2];
}

bool Sign::operator <(const Sign& other) const {

    if (birthday[2] != other.birthday[2])
        return birthday[2] < other.birthday[2];

    if (birthday[1] != other.birthday[1])
        return birthday[1] < other.birthday[1];
    
    return birthday[0] < other.birthday[0];
}

bool Sign::operator >(const Sign& other) const {

    if (birthday[2] != other.birthday[2])
        return birthday[2] > other.birthday[2];
    
    if (birthday[1] != other.birthday[1])
        return birthday[1] > other.birthday[1];
    
    return birthday[0] > other.birthday[0];
}

const std::string& Sign::getName() const {

    return name;
}

const std::string& Sign::getLastName() const {

    return lastName;
}

const Zodiac Sign::getZodiac() const {

	return zodiac;
}

int* Sign::getBirthday() const {

    int* b = new int[3];
    b[0] = birthday[0];
    b[1] = birthday[1];
    b[2] = birthday[2];

    return b;
}

void Sign::setName(const std::string& name) {

    std::string trimmed = trim(name);
    if (trimmed.empty())
        throw std::invalid_argument("Cannot set null object");

    this->name = trimmed;
}

void Sign::setLastName(const std::string& lastName) {

    std::string trimmed = trim(lastName);
    if (trimmed.empty())
        throw std::invalid_argument("Cannot set null object");

    this->lastName = trimmed;
}

void Sign::setBirthday(int birthday[3]) {

    validateAndSetBirthday(birthday);
}

std::ostream& Signs::operator <<(std::ostream& os, const Sign& s) {

    os << s.name << " " << s.lastName << " ";
    os << to_string(s.zodiac) << " ";
    os << (s.birthday[0] < 10 ? "0" : "") << s.birthday[0] << "-"
        << (s.birthday[1] < 10 ? "0" : "") << s.birthday[1] << "-"
        << s.birthday[2];
    return os;
}

std::istream& Signs::operator >>(std::istream& is, Sign& s) {

    int day = 0, month = 0, year = 0;
    is >> s.name >> s.lastName >> day >> month >> year;

    int temp[3] = { day, month, year };
    if (!is || !s.validateAndSetBirthday(temp)) {
        std::cout << "Invalid input or birthday. Default set to 01-01-1900" << std::endl;
        int defaultBirthday[3] = { 1,1,1900 };
        s.validateAndSetBirthday(defaultBirthday);
    }

    return is;
}