#include "stats.h"
#include <algorithm>
using namespace std;
HttpRequest ParseRequest(string_view line)
{
    auto p = line.find_first_not_of(' ');
    line.remove_prefix(p);
    auto advance_and_remove = [&line]()
    {
        auto pos = line.find(' ');
        string_view str = string_view(line.data(), pos);
        line.remove_prefix(pos + 1);
        return str;
    };
    const string_view methode = advance_and_remove();
    const string_view uri = advance_and_remove();
    const string_view protocl = string_view(line.data());
    return {methode, uri, protocl};
}

Stats::Stats()
{
    for(const auto &method: METHOD)
    {
        methods[method] = 0;
    }
    methods[string_view("UNKNOWN")] = 0;
    for(const auto &uri: URI)
    {
        uris[uri] = 0;
    }
    uris[string_view("unknown")] = 0;
}

void Stats::add_to_dic(const string_view str, bool id)
{
    if (id)
    {
        auto itr = find(METHOD.begin(), METHOD.end(), str);
        if (itr != METHOD.end())
        {
            methods[METHOD[itr - METHOD.begin()]]++;
        }

        else
        {
            methods[string_view("UNKNOWN")]++;
        }
    }
    else
    {
        auto itr = find(URI.begin(), URI.end(), str);
        if (itr != URI.end())
        {
            uris[URI[itr - URI.begin()]]++;
        }

        else
        {
            uris[string_view("unknown")]++;
        }
    }
}

void Stats::AddMethod(string_view method)
{
    add_to_dic(method, true);
}

void Stats::AddUri(string_view uri)
{
    add_to_dic(uri, false);
}

const map<string_view, int> &Stats::GetMethodStats() const
{
    return methods;
}
const map<string_view, int> &Stats::GetUriStats() const
{
    return uris;
}
