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
    string  current = names[names.size() -1];
    for (int i = names.size() - 2; i >= 0; --i)
    {
        if(names[i] != current)
        {
            result += names[i] + ", ";
            current = names[i];
        }
    }
    result = result.substr(0, result.find_last_of(","));
    result = "(" + result + ")";
    result = " " + result;
    if (result == " ()" )
        return names[names.size() -1];
    result = names[names.size() - 1] + result;
    return result;
}

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        this->first_name[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        this->last_name[year] = last_name;
    }
    string GetFullName(int year)
    {
        string result;
        if (FindNameByYear(first_name, year).empty() && FindNameByYear(last_name, year).empty())
        {
            result = "Incognito";
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
    string GetFullNameWithHistory(int year)
    {
        string result;
        if (FindAllPreviousNames(first_name, year).empty() && FindAllPreviousNames(last_name, year).empty())
        {
            result = "Incognito";
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

    // string GetLastName(int year)
    // {
    //     string s = "";
    //     for (const auto &item : last_name)
    //     {
    //         if (item.first <= year)
    //         {
    //             s = item.second;
    //         }
    //     }
    //     return s;
    // }
    // string GetFirstName(int year)
    // {
    //     string s = "";
    //     for (const auto &item : first_name)
    //     {
    //         if (item.first <= year)
    //         {
    //             s = item.second;
    //         }
    //     }
    //     return s;
    // }

private:
    // приватные поля
    map<int, string> first_name;
    map<int, string> last_name;
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
