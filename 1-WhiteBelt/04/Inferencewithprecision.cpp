#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
int main()
{
    ifstream input("input.txt");
    double val;
    cout << fixed << setprecision(3);
    while (input >> val)
    {
        cout << val << endl;
    }
    return 0;
}