#include "responses.h"
ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (r.buses.size() == 0)
    {
        os << r.no_stop;
    }
    else
    {
        for (const auto &bus : r.buses)
        {
            os << bus << " ";
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.stops.size() == 0)
    {
        os << r.no_bus;
    }
    else
    {
        for (const auto &p : r.stops)
        {
            os << "Stop " << p.first << ": ";
            if (p.second.size() == 1)
            {
                os << r.no_interchange << endl;
            }
            else
            {
                for (const auto &bus : p.second)
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

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.buses.size() == 0)
    {
        os << r.no_buses;
    }
    else
    {
        for (const auto &p : r.buses)
        {
            os << "Bus " << p.first << ": ";
            for (const auto &stop : p.second)
            {
                os << stop << " ";
            }
            os << endl;
        }
    }

    return os;
}