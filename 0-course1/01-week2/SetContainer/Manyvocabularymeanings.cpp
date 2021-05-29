// #include <iostream>
// #include <string>
// #include <set>
// #include <map>
// using namespace std;
set<string> BuildMapValuesSet(const map<int, string> &values)
{
    set<string> result;
    for (const auto &item : values)
    {
        result.insert(item.second);
    }
    return result;
}
// int main()
// {
    // set<string> values = BuildMapValuesSet({{1, "odd"}, {2, "even"}, {3, "odd"}, {4, "even"}, {5, "odd"}});
    // for (const string &value : values)
    // {
        // cout << value << endl;
    // }
    // return 0;
// }