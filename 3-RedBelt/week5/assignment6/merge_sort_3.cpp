#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
  if (distance(range_begin, range_end) < 2)
  {
    return;
  }
  else
  {
    vector<typename RandomIt::value_type> tmp(make_move_iterator(range_begin), make_move_iterator(range_end));
    RandomIt f_third = tmp.begin() + tmp.size() / 3;
    RandomIt s_third = f_third + tmp.size() / 3;
    MergeSort(tmp.begin(), f_third);
    MergeSort(f_third, s_third);
    MergeSort(s_third, tmp.end());
    vector<typename RandomIt::value_type> tmp2;
    merge(make_move_iterator(tmp.begin()),
          make_move_iterator(f_third),
          make_move_iterator(f_third),
          make_move_iterator(s_third),
          move(back_inserter(tmp2)));
    merge(make_move_iterator(tmp2.begin()),
          make_move_iterator(tmp2.end()),
          make_move_iterator(s_third),
          make_move_iterator(tmp.end()),
          range_begin);
  }
}

void TestIntVector()
{
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}