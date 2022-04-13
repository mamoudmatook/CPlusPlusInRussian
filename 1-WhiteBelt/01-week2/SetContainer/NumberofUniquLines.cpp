#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    set<string> lines;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        string tmp;
        cin >> tmp;
        lines.insert(tmp);
    }
    cout << lines.size() << endl;
    return 0;
}