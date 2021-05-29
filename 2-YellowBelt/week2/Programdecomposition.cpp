#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q)
{

    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        vector<string> &stops = q.stops;
        stops.resize(stop_count);
        for (string &stop : stops)
        {
            is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {

        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else
    {
        q.type = QueryType::AllBuses;
    }
    return is;
};

struct BusesForStopResponse
{
    string no_stop = "No stop";
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if(r.buses.size() == 0)
    {
        os << r.no_stop;
    }
    else
    {
        for (const auto &bus: r.buses)
        {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse
{
    string no_bus = "No bus";
    string no_interchange = "no interchange";
    string bus;
    vector<pair<string, vector<string>>> stops;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.stops.size() == 0)
    {
        os << r.no_bus; 
    }
    else
    {
        for(const auto &p : r.stops)
        {
            os << "Stop " << p.first << ": "; 
            if ( p.second.size() == 1)
            {
                os << r.no_interchange << endl; 
            }
            else
            {
                for (const auto &bus: p.second)
                {
                    if (bus != r.bus) 
                    {
                        os << bus << " ";
                    }
                }
                os << endl;
            }
            
        } 
    }
    return os;
}

struct AllBusesResponse
{
    string no_buses = "No buses";
    map <string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if(r.buses.size() == 0)
    {
        os << r.no_buses;
    }
    else
    {
        for (const auto &p: r.buses)
        {
            os << "Bus " << p.first << ": ";
            for (const auto &stop: p.second)
            {
                os << stop << " ";
            }
            os << endl;
        }
    }
    
    return os;
}

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        for(const auto &stop : stops)
        {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
    {
        BusesForStopResponse result;
        if(stops_to_buses.count(stop) != 0 )
        {
            result.buses = stops_to_buses.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const
    {
        StopsForBusResponse result;
        result.bus = bus;
        if (buses_to_stops.count(bus) != 0)
        {
            for(const auto &stop: buses_to_stops.at(bus))
            {
                result.stops.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        
        return result;
    }

    AllBusesResponse GetAllBuses() const
    {
        AllBusesResponse result;
        result.buses = buses_to_stops;
        return result;
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// ÐÐµ Ð¼ÐµÐ½ÑÑ Ñ‚ÐµÐ»Ð° Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ main, Ñ€ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ Ð¸ ÐºÐ»Ð°ÑÑÑ‹ Ð²Ñ‹ÑˆÐµ

int main()
{
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}