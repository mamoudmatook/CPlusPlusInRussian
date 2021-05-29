#include <vector>
#include <algorithm>
using namespace std;
template <typename T>
void RemoveDuplicates(vector<T>& elements)
{
    sort(elements.begin(), elements.end());
    auto itr = unique(elements.begin(), elements.end());
    elements.erase(itr, elements.end());
}