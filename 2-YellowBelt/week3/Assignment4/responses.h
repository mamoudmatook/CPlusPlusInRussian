#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct BusesForStopResponse
{
    string no_stop = "No stop";
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse
{
    string no_bus = "No bus";
    string no_interchange = "no interchange";
    string bus;
    vector<pair<string, vector<string> > > stops;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse
{
    string no_buses = "No buses";
    map<string, vector<string> > buses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);
