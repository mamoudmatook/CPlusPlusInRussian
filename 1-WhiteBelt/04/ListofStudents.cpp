#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Student
{
    string f_name;
    string l_name;
    int day, month, year;
};
int main()
{
    vector<Student> students;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string f, l;
        int d, m, y;
        cin >> f >> l >> d >> m >> y;
        students.push_back({f, l, d, m, y});
    }
    int q;
    cin >> q;
    for (int j = 0; j < q; j++)
    {
        string command;
        int k;
        cin >> command >> k;
        if (command == "name" && k >= 1 && k <= students.size())
        {
            cout << students[k - 1].f_name << " " << students[k - 1].l_name << endl;
        }
        else if (command == "date" && k >= 1 && k <= students.size())
        {
            cout << students[k - 1].day << "." << students[k - 1].month << "." << students[k - 1].year << endl;
        }
        else
        {
            cout << "bad request" << endl;
        }
    }
    return 0;
}