#include "test_runner.h"
#include <string>
#include <vector>
#include <map>
#include <string_view>
#include <deque>

using namespace std;

class Translator
{
public:
    void Add(string_view source, string_view target)
    {
        auto source_view = get_cloned_view(source);
        auto target_view = get_cloned_view(target);
        _forward[source_view] = target_view;
        _backward[target_view] = source_view;
    }
    string_view TranslateForward(string_view source) const
    {
        return translate(source, _forward);
    }
    string_view TranslateBackward(string_view target) const
    {
        return translate(target, _backward);
    }

private:
    map<string_view, string_view> _forward;
    map<string_view, string_view> _backward;
    deque<string> _buffer;
    string_view get_cloned_view(string_view str)
    {
        for (const auto *map_str : {&_forward, &_backward})
        {
            const auto it = map_str->find(str);
            if (it != map_str->end())
            {
                return it->first;
            }
        }
        return _buffer.emplace_back(str);
    }
    string_view translate(string_view str, const map<string_view, string_view> &dict) const
    {
        const auto it = dict.find(str);
        return it != dict.end() ? it->second : string_view{};
    }
};

void TestSimple()
{
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}