#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector
{
public:
    explicit StackVector(size_t a_size = 0) : _size{a_size}
    {
        if (_size > N)
        {
            throw invalid_argument("invalid size");
        }
    }

    T &operator[](size_t index)
    {
        return _data[index];
    }
    const T &operator[](size_t index) const
    {
        return _data[index];
    }

    auto begin()
    {
        return _data.begin();
    }
    auto end()
    {
        return _data.begin() + _size;
    }
    auto begin() const
    {
        return _data.begin();
    }
    auto end() const
    {
        return _data.begin() + _size;
    }

    size_t Size() const
    {
        return _size;
    }
    size_t Capacity() const
    {
        return N;
    }

    void PushBack(const T &value)
    {
        if (_size == N)
        {
            throw overflow_error("over flow !!");
        }
        _data[_size++] = value;
    }
    T PopBack()
    {
        if (!_size)
        {
            throw underflow_error("under flow !!!");
        }
        return _data[--_size];
    }

private:
    size_t _size = 0;
    array<T, N> _data;
};
