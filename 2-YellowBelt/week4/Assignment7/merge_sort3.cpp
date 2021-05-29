#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (distance(range_begin, range_end) < 2)
    {
        return;
    }
    vector<typename RandomIt::value_type> cpy(range_begin, range_end);
    auto m1 = cpy.begin() + cpy.size() / 3;
    auto m2 = m1 + cpy.size() / 3;
    MergeSort(cpy.begin(), m1);
    MergeSort(m1, m2);
    MergeSort(m2, cpy.end());
    vector<typename RandomIt::value_type> tmp;
    merge(cpy.begin(), m1, m1, m2, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), m2, cpy.end(), range_begin);
}
int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}