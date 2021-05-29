#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool compare(int x, int y)
{
    return abs(x) < abs(y);
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto &i: nums)
    {
        cin >> i;
    };
    sort(nums.begin(),nums.end(), compare);
    for (const auto &i: nums)
    {
        cout << i << " ";
    }
    cout << endl;
}