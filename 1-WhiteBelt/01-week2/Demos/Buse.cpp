#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
vector<string> BusesForStop(const map<string, vector<string>> &bus_storage,
                            const string &stop)
{
    vector<string> stops;
    for (auto &bus : bus_storage)
    {
        if (find(bus.second.begin(), bus.second.end(), stop) != bus.second.end())
        {
            stops.push_back(bus.first);
        }
    }
    return stops;
}

vector<string> BusesForStop(const map<string, vector<string>> &bus_storage,
                            const string &stop, const string &org_bus)
{
    vector<string> stops;
    for (auto &bus : bus_storage)
    {
        if (bus.first != org_bus && find(bus.second.begin(), bus.second.end(), stop) != bus.second.end())
        {
            stops.push_back(bus.first);
        }
    }
    return stops;
}
//
//vector<string> AllBuses(const map<string, vector<string>> &bus_storage, const string &bus) {
//	vector<string> bus_stops;
//	auto &stops = bus_storage[bus];
//	for (auto &stop: stops) {
//		bus_stops.push_back(stop);
//	}
//	return bus_stops;
//}

int main()
{
    map<string, vector<string>> bus_storage;
    map<string, vector<string>> stops;
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        string command;
        cin >> command;
        if (command == "NEW_BUS")
        {
            string bus;
            int stop_count;
            cin >> bus >> stop_count;
            vector<string> bus_stops(stop_count);
            for (auto &stop : bus_stops)
            {
                cin >> stop;
                vector<string> v;
                v.push_back(bus);
                if(stops.count(stop))
                {
                    stops[stop].insert(stops[stop].end(), v.begin(), v.end());
                }
                else
                {
                    stops[stop] = v;
                }
            }
            bus_storage[bus] = bus_stops;
        }
        else if (command == "BUSES_FOR_STOP")
        {
            string stop;
            cin >> stop;
            if(stops.find(stop) == stops.end())
            {
                cout << "No stop" << endl;
            }
            else
            {
                auto &buses = stops[stop];
                for (auto &bus : buses) 
                {
                    cout << bus << " ";
                }
                cout << endl;
            }
            
        }
        else if (command == "STOPS_FOR_BUS")
        {
            string bus;
            cin >> bus;
            if (bus_storage.find(bus) == bus_storage.end())
            {
                cout << "No bus" << endl;
            }
            else
            {
                for (auto &stop : bus_storage[bus])
                {
                    if (stops[stop].size() == 1 && stops[stop][0] == bus)
                    {
                        cout << "Stop " << stop << ": no interchange" << endl;
                    }
                    else
                    {
                        cout << "Stop " << stop << ": "; 
                        for (auto &bus1: stops[stop])
                        {
                            if (bus1 != bus)
                            {
                                cout << bus1 << " ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
        }
        else
        {
            if (bus_storage.size() == 0)
            {
                cout << "No buses" << endl;
            }
            else
            {
                for (auto &bus : bus_storage)
                {
                    auto bus_stops = bus.second;
                    cout << "Bus " << bus.first << ": ";
                    for (auto &stop : bus_stops)
                    {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}