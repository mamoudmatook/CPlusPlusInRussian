#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int cnt = 0;
    map<set<string>, int> stop;
    for (int i = 0; i < n; i++)
    {
        int nums;
        cin >> nums;
        set<string> tmp;
        for (int i = 0; i < nums; i++)
        {
            string t;
            cin >> t;
            tmp.insert(t);
        }
        if (stop.find(tmp) == stop.end())
        {
            stop[tmp] = ++cnt;
            cout << "New bus " << cnt << endl;
        }
        else
        {
            cout << "Already exists for " << stop[tmp] << endl;
        }
    }
    return 0;
}