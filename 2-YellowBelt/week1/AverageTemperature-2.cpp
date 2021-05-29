#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int N;
    cin >> N;
    if (N == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    vector<int> temps(N);
    int64_t sum = 0;
    for (auto &i : temps)
    {
        cin >> i;
        sum += i;
    }
    int a_mean = sum / N;
    vector<int> high_tmps;
    int k = 0;
    for (int i = 0; i < static_cast<int>(temps.size()); i++)
    {
        if (temps[i] > a_mean)
        {
            k++;
            high_tmps.push_back(i);
        }
    }
    cout << k << endl;
    for (auto &i : high_tmps)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}