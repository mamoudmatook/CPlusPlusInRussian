#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <queue>
// Warning, long feedback: only the beginning and the end of the feedback message is shown, and the middle was replaced by " ... ". Compile error: b"In file included from /tmp/submissionwd60o54q/priority_collection.cpp:1:\nIn file included from include/test_runner.h:3:\nIn file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/sstream:38:\nIn file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/istream:38:\nIn file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/ios:40:\nIn file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/char_traits.h:39:\nIn file included from /usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_algobase.h:64:\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:572:14: fatal error: no matching constructor for initialization of '__pair_type' (aka 'pair<__CourseraNonCopyable<int>, int>')\n      return __pair_type(std::forward<_T1>(__x), std::forward<_T2>(__y));\n             ^           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n/tmp/submissionwd60o54q/priority_collection.cpp:61:16: note: in instantiation of function template specialization 'std::make_pair<const __CourseraNonCopyable<int> &, const int &>' requested here\n        return make_pair(p.data, p.priority);\n               ^\n/tmp/submissionwd60o54q/priority_collection.cpp:266:45: note: in instantiation of member function 'PriorityCollection<__CourseraNonCopyable<int> >::GetMax' requested here\n        auto [value, priority] = collection.GetMax();\n                                            ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:266:17: note: candidate template ignored: requirement '_PCC<true, __CourseraNonCopyable<int>, int>::_ConstructiblePair()' was not satisfied [with _U1 = __CourseraNonCopyable<int>, _U2 = int]\n      constexpr pair(const _T1& __a, const _T2& __b)\n                ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:276:26: note: candidate template ignored: requirement '_PCC<true, __CourseraNonCopyable<int>, int>::_ConstructiblePair()' was not satisfied [with _U1 = __CourseraNonCopyable<int>, _U2 = int]\n      explicit constexpr pair(const _T1& __a, const _T2& __b)\n                         ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:322:18: note: candidate template ignored: requirement '_PCC<true, __Course ... , _U2>& __p)\n                  ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:309:21: note: candidate constructor template not viable: requires single argument '__p', but 2 arguments were provided\n        explicit constexpr pair(const pair<_U1, _U2>& __p)\n                           ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:314:17: note: candidate constructor not viable: requires 1 argument, but 2 were provided\n      constexpr pair(const pair&) = default;    ///< Copy constructor\n                ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:315:17: note: candidate constructor not viable: requires 1 argument, but 2 were provided\n      constexpr pair(pair&&) = default;         ///< Move constructor\n                ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:371:12: note: candidate constructor template not viable: requires single argument '__p', but 2 arguments were provided\n        constexpr pair(pair<_U1, _U2>&& __p)\n                  ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:381:21: note: candidate constructor template not viable: requires single argument '__p', but 2 arguments were provided\n        explicit constexpr pair(pair<_U1, _U2>&& __p)\n                           ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:387:9: note: candidate constructor template not viable: requires 3 arguments, but 2 were provided\n        pair(piecewise_construct_t, tuple<_Args1...>, tuple<_Args2...>);\n        ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:232:26: note: candidate constructor template not viable: requires 0 arguments, but 2 were provided\n      _GLIBCXX_CONSTEXPR pair()\n                         ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:245:26: note: candidate constructor template not viable: requires 0 arguments, but 2 were provided\n      explicit constexpr pair()\n                         ^\n/usr/bin/../lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10/bits/stl_pair.h:452:9: note: candidate constructor template not viable: requires 4 arguments, but 2 were provided\n        pair(tuple<_Args1...>&, tuple<_Args2...>&,\n        ^\n1 error generated.\n"
using namespace std;

template <typename T>
class PriorityCollection
{

public:
    using Id = int;

    Id Add(T object)
    {
        Id id = objects.size();
        objects.push_back({move(object)});
        sorted_objects.insert(make_pair(0, id));
        return id;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin)
    {
        while (range_begin != range_end)
        {
            *ids_begin++ = Add(move(*range_begin++));
        }
    }

    bool IsValid(Id id) const
    {
        return id >= 0 && id < static_cast<int>(objects.size()) &&
               objects[id].priority != -1;
    }

    const T &Get(Id id) const
    {
        return objects[id].data;
    }

    void Promote(Id id)
    {
        Object &tmp = objects[id];
        int old_pr = tmp.priority;
        int new_pr = ++tmp.priority;
        sorted_objects.erase(make_pair(old_pr, id));
        sorted_objects.insert(make_pair(new_pr, id));
    }

    pair<const T &, int> GetMax() const
    {
        auto &p = objects[prev(sorted_objects.end())->second];
        return {p.data, p.priority};
    }

    pair<T, int> PopMax()
    {
        auto itr = prev(sorted_objects.end());
        auto &item = objects[itr->second];
        sorted_objects.erase(itr);
        int priority = item.priority;
        item.priority = -1;
        return {move(item.data), priority};
    }

private:
    struct Object
    {
        T data;
        int priority = 0;
    };
    vector<Object> objects;
    set<pair<int, Id> > sorted_objects;
};

class StringNonCopyable : public string
{
public:
    using string::string; // ÐŸÐ¾Ð·Ð²Ð¾Ð»ÑÐµÑ‚ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€Ñ‹ ÑÑ‚Ñ€Ð¾ÐºÐ¸
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}