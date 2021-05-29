#include <algorithm>
#include <string>
#include <utility>
#include <iostream>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    
    auto pr = equal_range(range_begin, range_end, string(1,prefix) ,[] (const string &st1, const string &st2) {cout << st1 << endl; return st1[0] < st2[0];});
    return make_pair(pr.first, pr.second);
}
//, [] (const string &st1, const string &st2) {return st1[0] < st2[0];}