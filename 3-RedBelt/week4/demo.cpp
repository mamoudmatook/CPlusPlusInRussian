#include <vector>
#include <iostream>
using namespace std;
int main()
{
    vector<int>v = {1, 2, 3};
    int &first = v[0];
    for(int i =0; i < 10000; ++i)
    {
        v.push_back(i);
    }
    cout << first << endl;
    return 0;
}