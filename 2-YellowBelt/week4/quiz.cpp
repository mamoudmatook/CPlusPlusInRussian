#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
void Print(const vector<int> &v)
{
  for (auto i : v)
  {
    cout << i << " ";
  }
  cout << endl;
}
bool f(int n)
{
  return n > 0;
}
int main()
{
  /*
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    auto it = remove_if(begin(v), end(v), f);
    v.erase(it, end(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    auto it = partition(begin(v), end(v), f);
    v.erase(it, end(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    sort(begin(v), end(v),
         [](int lhs, int rhs) { return f(lhs) > f(rhs); });
    Print(v);
    auto it = partition_point(begin(v), end(v), f);
    Print(v);
    v.erase(begin(v), it);
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    auto it = partition(begin(s), end(s), f);
    copy(it, end(s), back_inserter(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    remove_copy_if(begin(s), end(s), back_inserter(v),
                   [](int x) { return !f(x); });
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    auto it = remove_if(begin(s), end(s),
                        [](int x) { return !f(x); });
    copy(it, end(s), back_inserter(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    Print(v);
    auto it = remove_if(begin(v), end(v),
                        [](int x) { return !f(x); });
    v.erase(it, end(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    copy_if(begin(s), end(s), back_inserter(v),
            [](int x) { return !f(x); });
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    sort(begin(v), end(v),
         [](int lhs, int rhs) { return f(lhs) > f(rhs); });
    auto it = partition_point(begin(v), end(v), f);
    v.erase(it, end(v));
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    v.assign(begin(s), end(s));
    auto it = partition(begin(v), end(v), f);
    v.erase(begin(v), it);
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    vector<int> garbage;
    partition_copy(
        begin(s), end(s),
        back_inserter(v), back_inserter(garbage), f);
    Print(v);
  }
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    vector<int> garbage;
    partition_copy(
        begin(s), end(s),
        back_inserter(garbage), back_inserter(v), f);
    Print(v);
  }
  */
  {
    set<int> s{-1, -2, -3, 1, 2, 3};
    vector<int> v;
    remove_copy_if(begin(s), end(s), back_inserter(v), f);
    Print(v);
  }
  return 0;
}