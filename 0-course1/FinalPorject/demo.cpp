#include <iostream>
#include <string>
using namespace std;
struct demo
{
    int x, y;
};

istream &operator>>(istream &input, demo &s)
{
    int x, y;
    input >> x >> y;
    s = {x, y};
    input.seekg(0);
    return input;
}
int main()
{
    demo l;
    cin >> l;
    cout << cin.tellg() << endl;
    cout << l.x << l.y << endl;
    return 0;
}