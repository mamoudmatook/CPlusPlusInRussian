#include <iostream>
using namespace std;
int main()
{
    uint n, r;
    cin >> n >> r;
    uint64_t mass = 0;
    uint w, h, d;
    for (uint i = 0; i < n; i++)
    {
        cin >> w >> h >> d;
        mass += static_cast<uint64_t>(w) * static_cast<uint64_t>(h) * static_cast<uint64_t>(d);
    }
    cout << mass * r << endl;
}