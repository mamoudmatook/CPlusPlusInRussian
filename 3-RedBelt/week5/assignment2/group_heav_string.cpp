#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <utility>
// Warning, long feedback: only the beginning and the end of the feedback message is shown, and the middle was replaced by " ... ". Compile error: b"/tmp/submission35j3a63b/group_heavy_strings.cpp:28:43: fatal error: call to implicitly-deleted default constructor of 'unordered_map<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, Group<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > >' (aka 'unordered_map<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, vector<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > >')\n    unordered_map<String, Group<String> > hmap;\n                                          ^\n/tmp/submission35j3a63b/group_heavy_strings.cpp:171:19: note: in instantiation of function template specialization 'GroupHeavyStrings<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >' requested here\n    auto groups = GroupHeavyStrings(strings); //one copy used\n                  ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/unordered_map.h:141:7: note: explicitly defaulted function was implicitly deleted here\n      unordered_map() = default;\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/unordered_map.h:105:18: note: default constructor of 'unordered_map<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::vector<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::allocator<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > >, std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >, std::equal_to<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >, std::allocator<std::pair<const std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::vector<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::allocator<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > > > > >' is implicitly deleted because field '_M_h' has a deleted default constructor\n      _Hashtable _M_h;\n                 ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable.h:451:7: note: explicitly defaulted function was implicitly deleted here\n      _Hashtable() = default;\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable.h:174:7: note: default constructor of '_Hashtable<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::pair<const std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::vector<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, st ... detail::_Select1st, std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, _Hashtable_traits<true, false, true>::__hash_cached::value>' has a deleted default constructor\n  : public _Hash_code_base<_Key, _Value, _ExtractKey, _H1, _H2, _Hash,\n    ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable_policy.h:1368:7: note: explicitly defaulted function was implicitly deleted here\n      _Hash_code_base() = default;\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable_policy.h:1344:7: note: default constructor of '_Hash_code_base<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::pair<const std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::vector<std::vector<__CopyTracker, std::allocator<__CopyTracker> >, std::allocator<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > > >, std::__detail::_Select1st, std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, true>' is implicitly deleted because base class '_Hashtable_ebo_helper<1, std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > > >' has a deleted default constructor\n      private _Hashtable_ebo_helper<1, _H1>,\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable_policy.h:1112:7: note: explicitly defaulted function was implicitly deleted here\n      _Hashtable_ebo_helper() = default;\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/hashtable_policy.h:1110:7: note: default constructor of '_Hashtable_ebo_helper<1, std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >, true>' is implicitly deleted because base class 'std::hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >' has a deleted default constructor\n    : private _Tp\n      ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/functional_hash.h:101:19: note: default constructor of 'hash<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >' is implicitly deleted because base class '__hash_enum<std::vector<__CopyTracker, std::allocator<__CopyTracker> > >' has no default constructor\n    struct hash : __hash_enum<_Tp>\n                  ^\n1 error generated.\n"

using namespace std;

// ÐžÐ±ÑŠÑÐ²Ð»ÑÐµÐ¼ Group<String> Ð´Ð»Ñ Ð¿Ñ€Ð¾Ð¸Ð·Ð²Ð¾Ð»ÑŒÐ½Ð¾Ð³Ð¾ Ñ‚Ð¸Ð¿Ð° String
// ÑÐ¸Ð½Ð¾Ð½Ð¸Ð¼Ð¾Ð¼ vector<String>.
// Ð‘Ð»Ð°Ð³Ð¾Ð´Ð°Ñ€Ñ ÑÑ‚Ð¾Ð¼Ñƒ Ð² ÐºÐ°Ñ‡ÐµÑÑ‚Ð²Ðµ Ð²Ð¾Ð·Ð²Ñ€Ð°Ñ‰Ð°ÐµÐ¼Ð¾Ð³Ð¾ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
// Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ Ð¼Ð¾Ð¶Ð½Ð¾ ÑƒÐºÐ°Ð·Ð°Ñ‚ÑŒ Ð½Ðµ Ð¼Ð°Ð»Ð¾Ð¿Ð¾Ð½ÑÑ‚Ð½Ñ‹Ð¹ Ð²ÐµÐºÑ‚Ð¾Ñ€ Ð²ÐµÐºÑ‚Ð¾Ñ€Ð¾Ð²,
// Ð° Ð²ÐµÐºÑ‚Ð¾Ñ€ Ð³Ñ€ÑƒÐ¿Ð¿ â€” vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ð•Ñ‰Ñ‘ Ð¾Ð´Ð¸Ð½ ÑˆÐ°Ð±Ð»Ð¾Ð½Ð½Ñ‹Ð¹ ÑÐ¸Ð½Ð¾Ð½Ð¸Ð¼ Ñ‚Ð¸Ð¿Ð°
// Ð¿Ð¾Ð·Ð²Ð¾Ð»ÑÐµÑ‚ Ð²Ð¼ÐµÑÑ‚Ð¾ Ð³Ñ€Ð¾Ð¼Ð¾Ð·Ð´ÐºÐ¾Ð³Ð¾ typename String::value_type
// Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
using Key = String;

template <typename String>
vector<Group<String> > GroupHeavyStrings(vector<String> strings)
{
    map<Key<String>, Group<String> > hmap;
    for (String &s : strings)
    {
        String sorted_str = s;
        sort(sorted_str.begin(), sorted_str.end());
        sorted_str.erase(unique(begin(sorted_str), end(sorted_str)), end(sorted_str));
        hmap[move(sorted_str)].push_back(move(s));
    }
    vector<Group<String> > result;
    for (auto &p : hmap)
    {
        result.push_back(move(p.second));
    }
    return result;
}

void TestGroupingABC()
{
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups)); // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
    ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal()
{
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups)); // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}