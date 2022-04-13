#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{

    ifstream input("input.txt");
    if (input.is_open())
    {
        int m, n;
        input >> m >> n;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                input >> tmp;
                cout << setw(10) << tmp;
                input.ignore(1);
                if (j != n - 1)
                {
                    cout << " ";
                }
            }
            if (i != m - 1)
            {
                cout << endl;
            }
        }
    }
    return 0;
}