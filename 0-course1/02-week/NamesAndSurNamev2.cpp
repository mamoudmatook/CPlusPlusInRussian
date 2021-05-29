#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;
vector<string> FindAllPreviousNames(const map<int, string> &names, int year)
{
    vector<string> result;
    for (const auto &item : names)
    {
        if (item.first <= year)
        {
            result.push_back(item.second);
        }
        else
        {
            break;
        }
    }
    return result;
}

string FindNameByYear(const map<int, string> names, int year)
{
    string result;
    for (const auto &item : names)
    {
        if (item.first <= year)
        {
            result = item.second;
        }
        else
        {
            break;
        }
    }
    return result;
}

string VectorToNames(const vector<string> &names)
{
    string result;
    string current = names[names.size() - 1];
    for (int i = names.size() - 2; i >= 0; --i)
    {
        if (names[i] != current)
        {
            result += names[i] + ", ";
            current = names[i];
        }
    }
    result = result.substr(0, result.find_last_of(","));
    result = "(" + result + ")";
    result = " " + result;
    if (result == " ()")
        return names[names.size() - 1];
    result = names[names.size() - 1] + result;
    return result;
}

class Person
{
public:
    Person(const string &f_name, const string &l_name, int year)
    {
        first_name[year] = f_name;
        last_name[year] = l_name;
        date_of_birth = year;
    }
    void ChangeFirstName(int year, const string &first_name)
    {
        if (year < date_of_birth)
            return;
        this->first_name[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        if (year < date_of_birth)
            return;
        this->last_name[year] = last_name;
    }
    string GetFullName(int year) const
    {
        string result;
        if (FindNameByYear(first_name, year).empty() && FindNameByYear(last_name, year).empty())
        {
            result = "No person";
        }
        else if (FindNameByYear(last_name, year).empty())
        {
            result = FindNameByYear(first_name, year) + " with unknown last name";
        }
        else if (FindNameByYear(first_name, year) == "")
        {
            result = FindNameByYear(last_name, year) + " with unknown first name";
        }
        else
        {
            result = FindNameByYear(first_name, year) + " " + FindNameByYear(last_name, year);
        }
        return result;
    }
    string GetFullNameWithHistory(int year) const
    {
        string result;
        if (FindAllPreviousNames(first_name, year).empty() && FindAllPreviousNames(last_name, year).empty())
        {
            result = "No person";
        }
        else if (FindAllPreviousNames(last_name, year).empty())
        {
            auto tmp = FindAllPreviousNames(first_name, year);
            if (tmp.size() > 1)
            {
                result = VectorToNames(tmp);
            }
            else
            {
                result += tmp[0];
            }
            result += " with unknown last name";
        }
        else if (FindAllPreviousNames(first_name, year).empty())
        {
            auto tmp = FindAllPreviousNames(last_name, year);
            if (tmp.size() > 1)
            {
                result = VectorToNames(tmp);
            }
            else
            {
                result += tmp[0];
            }
            result += " with unknown first name";
        }
        else
        {
            auto tmp1 = FindAllPreviousNames(first_name, year);
            if (tmp1.size() > 1)
            {
                result += VectorToNames(tmp1);
            }
            else
            {
                result += tmp1[0];
            }
            result += " ";
            auto tmp2 = FindAllPreviousNames(last_name, year);
            if (tmp2.size() > 1)
            {
                result += VectorToNames(tmp2);
            }
            else
            {
                result += tmp2[0];
            }
        }
        return result;
    }

private:
    // приватные поля
    map<int, string> first_name;
    map<int, string> last_name;
    int date_of_birth;
};

// int main()
// {
// Person person("Polina", "Sergeeva", 1960);
// for (int year : {1959, 1960})
// {
// cout << person.GetFullNameWithHistory(year) << endl;
// }

// person.ChangeFirstName(1965, "Appolinaria");
// person.ChangeLastName(1967, "Ivanova");
// for (int year : {1965, 1967})
// {
// cout << person.GetFullNameWithHistory(year) << endl;
// }

// return 0;
// }
