#include <iostream>
#include <vector>
#include <list>
using Position = std::list<int>::iterator;

int main()
{
    const int Max_NUM = 100000;
    std::list<int> row;
    std::vector<Position> positions(Max_NUM + 1, row.end());
    int num_of_athletes;
    std::cin >> num_of_athletes;
    for(auto i = 0; i < num_of_athletes; ++i)
    {
        int c_athlete, n_athlete;
        std::cin >> c_athlete >> n_athlete;
        positions[c_athlete] = row.insert(positions[n_athlete], c_athlete);
    }
    for(auto a: row)
    {
        std::cout << a << std::endl;
    }
    return 0;
}