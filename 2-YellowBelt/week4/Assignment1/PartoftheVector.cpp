#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;
void PrintVectorPart(const vector<int>& numbers)
{
    auto it = find_if(begin(numbers), end(numbers), [](int num){return num  < 0;});
    for (auto t = it; t != numbers.begin();)
    {
        cout << *(--t) << " ";
    }
}













