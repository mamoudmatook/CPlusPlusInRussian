#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
T Sqr(T element);

template <typename first, typename second>
pair<first, second> operator*(const pair<first, second> &p1, const pair<first, second> &p2);

template <typename T>
vector<T> operator*(const vector<T> &v1, const vector<T> &v2);

template <typename key, typename val>
map<key, val> operator*(const map<key, val> &m1, const map<key, val> &m2);

template <typename T>
T Sqr(T element)
{
    return element *element;
}

template <typename first, typename second>
pair<first, second> operator*(const pair<first, second> &p1, const pair<first, second> &p2)
{
    pair<first, second> p3;
    p3.first = p1.first * p2.first;
    p3.second = p1.second * p2.second;
    return p3;
}

template <typename T>
vector<T> operator*(const vector<T> &v1, const vector<T> &v2)
{
    //check if 2 vectors of the same size
    vector<T> result;
    for (auto i = 0; i < v1.size(); i++)
    {
        result.push_back(v1[i] * v2[i]);
    }
    return result;
}

template <typename key, typename val>
map<key, val> operator*(const map<key, val> &m1, const map<key, val> &m2)
{
    // map multiplication in general should be different;
    map<key, val> result;
    for (const auto &p : m1)
    {
        result[p.first] = m1.at(p.first) * m2.at(p.first);
    }
    return result;
}

// int main()
// {
//     // Пример вызова функции
//     vector<int> v = {1, 2, 3};
//     cout << "vector:";
//     for (int x : Sqr(v))
//     {
//         cout << ' ' << x;
//     }
//     cout << endl;

//     map<int, pair<int, int>> map_of_pairs = {
//         {4, {2, 2}},
//         {7, {4, 3}}};
//     cout << "map of pairs:" << endl;
//     for (const auto &x : Sqr(map_of_pairs))
//     {
//         cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
//     }
// }