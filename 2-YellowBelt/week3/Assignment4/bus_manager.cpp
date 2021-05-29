#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
    for (const auto &stop : stops)
    {
        buses_to_stops[bus].push_back(stop);
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
    BusesForStopResponse result;
    if (stops_to_buses.count(stop) != 0)
    {
        result.buses = stops_to_buses.at(stop);
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
    StopsForBusResponse result;
    result.bus = bus;
    if (buses_to_stops.count(bus) != 0)
    {
        for (const auto &stop : buses_to_stops.at(bus))
        {
            result.stops.push_back(make_pair(stop, stops_to_buses.at(stop)));
        }
    }

    return result;
}

AllBusesResponse BusManager::GetAllBuses() const
{
    AllBusesResponse result;
    result.buses = buses_to_stops;
    return result;
}
