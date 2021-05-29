#include <iostream>
#include "phone_number.h"

int main()
{
    std::string number;
    std::cin >> number;
    PhoneNumber p(number);
    std::cout << p.GetCountryCode() << std::endl;
    std::cout << p.GetCityCode() << std::endl;
    std::cout << p.GetLocalNumber() << std::endl;
    std::cout << p.GetInternationalNumber() << std::endl;
    return 0;
}