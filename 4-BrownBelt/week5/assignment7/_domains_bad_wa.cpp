#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_set>
using namespace std;
class Dfilter
{
public:
    Dfilter(unordered_set<string_view> domains) : bad_(move(domains)) {}
    bool is_good(string_view subdomain)
    {
        size_t pos = subdomain.rfind('.');
        while (pos != string_view::npos)
        {
            if (bad_.find(subdomain.substr(pos + 1)) != bad_.end())
            {
                return false;
            }
            pos = subdomain.rfind('.', pos - 1);
        }
        return bad_.find(subdomain) == bad_.end();
    }

private:
    unordered_set<string_view> bad_;
};

vector<string> ReadDomains(istream &in_stream = cin)
{
    vector<string> domains;

    size_t count;
    in_stream >> count;
    domains.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        string domain_text;
        in_stream >> domain_text;
        domains.push_back(move(domain_text));
    }
    return domains;
}

int main()
{
    const vector<string> banned_domains = ReadDomains();
    const vector<string> domains_to_check = ReadDomains();
    Dfilter filter(unordered_set<string_view>(banned_domains.begin(), banned_domains.end()));
    for (const string domain : domains_to_check)
    {
        if (filter.is_good(domain))
        {
            cout << "Good" << endl;
        }
        else
        {
            cout << "Bad" << endl;
        }
    }
    return 0;
}