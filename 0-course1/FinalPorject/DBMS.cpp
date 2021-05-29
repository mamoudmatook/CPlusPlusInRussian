#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
using namespace std;

class Date
{
public:
    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }
    Date() : year(1900), month(01), day(01)
    {
    }
    Date(int y, int m, int d)
    {
        if (!(m >= 1 && m <= 12))
        {
            string error = "Month value is invalid: " + to_string(m);
            throw invalid_argument(error);
        }
        if (!(d >= 1 && d <= 31))
        {
            string error = "Day value is invalid: " + to_string(d);
            throw invalid_argument(error);
        }
        else
        {
            year = y;
            month = m;
            day = d;
        }
    }

private:
    int year;
    int month;
    int day;
};

void CheckHyphenAndSkip(istream &input, const string &str_date)
{
    if (input.fail() || input.peek() != '-')
    {
        throw "Wrong date format: " + str_date;
    }
    input.ignore();
}
bool operator<(const Date &lhs, const Date &rhs)
{
    // return lhs.GetYear() < rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth() && lhs.GetDay() < rhs.GetDay();
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
           vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

// bool operator==(const Date &lhs, const Date &rhs)
// {
//     return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay();
// }

istream &operator>>(istream &in, Date &date)
{
    string s;
    in >> s;
    stringstream input(s);
    int y;
    input >> y;
    CheckHyphenAndSkip(input, s);
    int m;
    input >> m;
    CheckHyphenAndSkip(input, s);
    int d;
    input >> d;
    if (input.fail() || !input.eof())
    {

        throw "Wrong date format: " + s;
    }
    date = Date(y, m, d);
    return in;
}

ostream &operator<<(ostream &output, const Date &date)
{
    output << setfill('0') << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return output;
}
class Database
{
public:
    void AddEvent(const Date &date, const string &event)
    {
        db[date].insert(event);
    }
    bool DeleteEvent(const Date &date, const string &event)
    {
        if (db.find(date) != db.end())
        {
            if (db[date].find(event) != db[date].end())
            {
                db[date].erase(event);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    int DeleteDate(const Date &date)
    {
        if (db.find(date) != db.end())
        {
            int m = db[date].size();
            db.erase(date);
            return m;
        }
        return 0;
    }
    // check for date first
    void Find(const Date &date) const
    {

        if (db.find(date) != db.end())
        {
            auto &events = db.at(date);
            for (const auto &event : events)
            {
                cout << event << endl;
            }
        }
    }
    void Print() const
    {
        for (const auto &pair : db)
        {
            for (const auto &event : pair.second)
            {
                if (pair.first.GetYear() < 0)
                {
                    continue;
                }
                cout << pair.first << " " << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> db;
};

int main()
{
    Database db;

    string command;
    try
    {
        while (getline(cin, command))
        {
            if (command.empty())
            {
                continue;
            }
            stringstream input(command);
            string cmd;
            input >> cmd;
            if (cmd == "Add")
            {
                Date date;
                string event;
                input >> date >> event;
                db.AddEvent(date, event);
            }
            else if (cmd == "Del")
            {
                Date date;
                string event;
                if (input >> date >> event)
                {
                    if (db.DeleteEvent(date, event))
                    {
                        cout << "Deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Event not found" << endl;
                    }
                }
                else
                {
                    int N = db.DeleteDate(date);
                    cout << "Deleted " << N << " events" << endl;
                }
            }
            else if (cmd == "Find")
            {
                Date date;
                input >> date;
                db.Find(date);
            }
            else if (cmd == "Print")
            {
                db.Print();
            }
            else
            {
                cout << "Unknown command: " << cmd << endl;
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << '\n';
    }
    catch (const string &s)
    {
        cout << s << endl;
    }
    return 0;
}