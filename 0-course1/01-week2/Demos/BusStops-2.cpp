#include <iostream> 
#include <map>
#include <string> 
#include <vector>
using namespace std;
int main() 
{
    map<vector<string>, int> stops;
    int q;
    cin >> q;
    int cnt = 0;
    for (int i = 0; i < q; i++)
    {
        int num;
        cin >> num;
        vector<string> bus_stops(num);
        for (auto &stop: bus_stops)
        {
            cin >> stop;
        }
        if (stops.find(bus_stops) == stops.end())
        {
            cout << "New bus " << ++cnt << endl;
            stops[bus_stops] = cnt;
        }
        else
        {
            cout << "Already exists for " << stops[bus_stops] << endl;
        }
    }
    return 0;
}