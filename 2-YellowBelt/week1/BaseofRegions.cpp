#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

// enum class Lang
// {
//     DE,
//     FR,
//     IT
// };

// struct Region
// {
//     string std_name;
//     string parent_std_name;
//     map<Lang, string> names;
//     int64_t population;
// };

int FindMaxRepetitionCount(const vector<Region> &regions)
{
    map<Region, int> hist;
    int result = 0;
    for (const auto &region : regions)
    {
        result = max(result, ++hist[region]);
    }
    return result;
}

bool operator<(const Region &r1, const Region &r2)
{
    return tie(r1.std_name, r1.parent_std_name, r1.names, r1.population) < tie(r2.std_name, r2.parent_std_name, r2.names, r2.population);
}

// int main()
// {
//     cout << FindMaxRepetitionCount({
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//             })
//          << endl;

//     cout << FindMaxRepetitionCount({
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Toulouse",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  31},
//             })
//          << endl;

//     return 0;
// }
