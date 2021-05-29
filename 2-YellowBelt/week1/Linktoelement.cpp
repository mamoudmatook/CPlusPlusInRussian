#include <iostream>
#include <map>
using namespace std;
template <typename key, typename value>
value& GetRefStrict(map<key, value> &m, const key &k)
{
    if (m.count(k) == 0)
    {
        throw runtime_error("key not found!");
    }
    return m.at(k);
}

// int main()
// {
//     map<int, string> m = {{0, "value"}};
//     string &item = GetRefStrict(m, 0);
//     item = "newvalue";
//     cout << m[0] << endl; // выведет newvalue
// }