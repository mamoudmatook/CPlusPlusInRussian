#include "phone_number.h"
#include <sstream>
#include <stdexcept>

PhoneNumber::PhoneNumber(const string &international_number)
{
    stringstream ss(international_number);
    char sign = ss.get();
    getline(ss, country_code_, '-');
    getline(ss, city_code_, '-');
    getline(ss, local_number_);
    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty() )
    {
        throw invalid_argument("invalid format");
    }
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}
string PhoneNumber::GetCityCode() const
{
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const
{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}