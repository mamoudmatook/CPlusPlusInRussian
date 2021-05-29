#include <set>
#include <utility>
#include <iostream>
using namespace std;
int main()
{
    set<pair<int,int> > users;
    users.insert(pair(5,10));
    users.insert(pair(3, 8));
    for(const auto &p : users)
    {
        cout << p.first << ":" << p.second <<endl;
    }
    return 0;
}