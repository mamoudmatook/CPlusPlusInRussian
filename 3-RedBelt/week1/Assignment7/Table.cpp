#include "test_runner.h"
#include <vector>
#include <utility>
#include <iostream>

using namespace std;
template <typename T>
class Table
{
public:
    Table(size_t rows, size_t cols)
    {
        Resize(rows, cols);
    }
    void Resize(size_t rows, size_t cols)
    {
        _data.resize(rows);
        for (auto &col : _data)
        {
            col.resize(cols);
        }
    }
    const vector<T>& operator[](size_t index) const
    {
        return _data[index];
    }
    vector<T>& operator[](size_t index)
    {
        return _data[index];
    }
    pair<size_t, size_t> Size() const
    {
        if(!_data.empty() && !_data[0].empty())
        {
            return {_data.size(), _data[0].size()};
        }
        return {0,0};
    }

private:
    vector<vector<T> > _data;
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}