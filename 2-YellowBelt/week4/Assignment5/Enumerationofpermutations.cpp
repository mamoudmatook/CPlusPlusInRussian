#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
int main()
{
    int n; 
    cin >> n;
    vector <int> permutes(n);
    iota(permutes.rbegin(), permutes.rend(), 1);
    do
    {
        for (const auto &p: permutes)
        {
            cout << p << " ";
        }
        cout <<endl;
    } while (prev_permutation(permutes.begin(), permutes.end()));
    
}
