#include <iostream>
using namespace std;
class Incognizable
{
private:
    /* data */
    int a;
    int b;

public:
    Incognizable(/* args */)
    {
        a = 0;
        b = 0;
    }
    Incognizable(int v)
    {
        a = v;
    }
    Incognizable(int v1, int v2)
    {
        a = v1;
        b = v2;
    }
};

// int main()
// {
    // Incognizable a;
    // Incognizable b = {};
    // Incognizable c = {0};
    // Incognizable d = {0, 1};
    // return 0;
// }
