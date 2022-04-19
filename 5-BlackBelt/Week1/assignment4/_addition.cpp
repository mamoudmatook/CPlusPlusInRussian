#include <iostream>
#include <limits>
using namespace std;
int main() {
    int64_t a, b, Max_64, Min_64;
    Max_64 = numeric_limits<int64_t>::max();
    Min_64 = numeric_limits<int64_t>::min();
    string OverFlow = "Overflow!";
    cin >> a >> b;
    if (a < 0 && b < 0) {
        if (Min_64 - a <= b) {
            cout << a + b;
        }
        else {
            cout << OverFlow;
        }
    }
    else if (a > 0 && b > 0) {
        if (Max_64 - a >= b) {
            cout << a + b;
        }
        else {
            cout << OverFlow;
        }
    }
    else {
        cout << a + b;
    }
}