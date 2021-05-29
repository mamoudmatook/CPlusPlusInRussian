#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;
string FindNameByYear(const map<int, string> &names, const int &year)
{
    string name;
    auto m = names.upper_bound(year);
    if (m != names.begin())
    {
        name = (--m)->second;
    }
    return name;
}
class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        _firstNames[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        // добавить факт изменения фамилии на last_name в год year
        _lastNames[year] = last_name;
    }
    string GetFullName(int year)
    {
        string fName = FindNameByYear(_firstNames, year);
        string lName = FindNameByYear(_lastNames, year);
        if (fName.empty() && lName.empty())
        {
            return "Incognito";
        }
        else if (lName.empty())
        {
            return fName + " with unknown last name";
        }
        else if (fName.empty())
        {
            return lName + " with unknown first name";
        }
        else
        {
            return fName + " " + lName;
        }
    }

private:
    // приватные поля
    map<int, string> _firstNames, _lastNames;
};

// int main()
// {
//     Person person;

//     person.ChangeFirstName(1965, "Polina");
//     person.ChangeLastName(1967, "Sergeeva");
//     for (int year : {1900, 1965, 1990})
//     {
//         cout << person.GetFullName(year) << endl;
//     }

//     person.ChangeFirstName(1970, "Appolinaria");
//     for (int year : {1969, 1970})
//     {
//         cout << person.GetFullName(year) << endl;
//     }

//     person.ChangeLastName(1968, "Volkova");
//     for (int year : {1969, 1970})
//     {
//         cout << person.GetFullName(year) << endl;
//     }
//     return 0;
// }
