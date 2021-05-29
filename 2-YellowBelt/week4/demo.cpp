#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;
bool cmp(const string &st1, const string &st2)
{
    cout << st1.substr(0, st2.size())  << endl;
    return st1.substr(0, st2.size()) < st2;
}

int main()
{
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
    for (const auto str : sorted_strings)
    {
        cout << cmp(str, "mo") << endl;
    }
    return 0;
}
