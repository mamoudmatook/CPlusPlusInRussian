#include <iostream>
#include  <algorithm>
#include <vector>
using namespace std;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (distance(range_begin, range_end) < 2)
    {
        return;
    }
    vector <typename RandomIt::value_type> cpy(range_begin, range_end);
    auto m = cpy.begin() + cpy.size() / 2;
    MergeSort(cpy.begin(), m);
    MergeSort(m , cpy.end());
    merge(cpy.begin(), m,  m, cpy.end(), range_begin);
}
int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}