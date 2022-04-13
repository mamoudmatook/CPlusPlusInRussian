#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
bool compare(string x, string y)
{
    std::transform(x.begin(), x.end(), x.begin(),
    [](unsigned char c){ return std::tolower(c); });
    std::transform(y.begin(), y.end(), y.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return x < y;

}

int main()
{
   int n;
   cin >> n;
   vector<string> v(n);
   for(auto &c: v)
   {
       cin >> c;
   }
   sort(v.begin(), v.end(), compare);
   for(const auto &c: v)
   {
       cout << c <<" ";
   }
   cout << endl;
   
}
