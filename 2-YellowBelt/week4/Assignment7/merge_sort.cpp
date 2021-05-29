#include "merge_sort.h"
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_begin >= range_end)
    {
        return;
    }
    auto m = range_begin + (range_end - range_begin) / 2;
    MergeSort(range_begin, m);
    MergeSort(m + 1, range_end);
    merge(range_begin, range_begin, range_begin);
}