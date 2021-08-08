#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename It>
struct IteratorRange {
  It first, last;

  IteratorRange(It begin, It end)
    : first(begin)
    , last(end)
  {
  }
};

// template<typename T>
// auto MakeRange(T& container) {
//   return IteratorRange(container.begin(), container.end());
// }

int main()
{
  IteratorRange rng{1,5};
  for(auto i = rng.first; i < rng.last; i++)
  cout << i << endl;
  return 0;
}