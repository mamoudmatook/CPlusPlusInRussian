#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector <string> result;
    auto bgn = begin(s);
    while (true)
    {
        auto tmp = find_if(bgn, end(s),[](char v){return v == ' ';});
        if( tmp != end(s))
        {
            result.push_back(string(bgn, tmp));
            tmp++;
            bgn = tmp;
        }
        else
        {
            break;
        }
    }
    result.push_back(string(bgn, end(s)));
    
    return result;
}