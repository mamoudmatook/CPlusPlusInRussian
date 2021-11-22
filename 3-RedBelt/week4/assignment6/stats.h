#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
#include<string>
using namespace std;



class Stats
{
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int> &GetMethodStats() const;
    const map<string_view, int> &GetUriStats() const;

private:
    map<string_view, int> methods, uris;
    void add_to_dic(const string_view str, bool id);
    inline const static vector<string> METHOD = {"GET", "POST", "PUT", "DELETE"};
    inline const static vector<string> URI = {"/", "/order", "/product", "/basket", "/help"};


};

HttpRequest ParseRequest(string_view line);
