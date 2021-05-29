#include <vector>
#include <set>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    vector <T> result;
    for (auto it = elements.begin(); it != elements.end(); it++)
    {
        if (*it > border)
        {
            result.push_back(*it);
        }
    }
    return result;
}