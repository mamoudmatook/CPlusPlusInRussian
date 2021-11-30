#include <cstdlib>
#include <algorithm>
using namespace std;
#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector
{
public:
    SimpleVector()
    {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    explicit SimpleVector(size_t size)
    {
        data = new T[size];
        capacity = size;
        size = size;
    }
    SimpleVector(const SimpleVector &rhs) : data(new T[rhs.capacity]),
                                            size(rhs.size), capacity(rhs.capacity)
    {
        copy(rhs.begin(), rhs.end(), begin());
    }
    SimpleVector<T> &operator=(const SimpleVector &rhs)
    {
        delete[] data;
        data = new T[rhs.size];
        size = rhs.size;
        capacity = rhs.capacity;
        copy(rhs.begin(), rhs.end(), begin());
        return *this;
    }
    ~SimpleVector()
    {
        delete[] data;
    }

    T &operator[](size_t index)
    {
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        return data[index];
    }

    T *begin()
    {
        return data;
    }

    const T *begin() const
    {
        return data;
    }

    T *end()
    {
        return data + size;
    }
    const T *end() const
    {
        return data + size;
    }
    size_t Size() const
    {
        return size;
    }
    size_t Capacity() const
    {
        return capacity;
    }
    void PushBack(const T &value)
    {
        if (data == nullptr)
        {
            data = new T[1];
            data[size] = value;
            ++size;
            capacity = 1;
        }
        else if (size == capacity)
        {
            T *tmp = new T[size];
            for (auto i = 0; i < size; ++i)
            {
                tmp[i] = data[i];
            }
            delete[] data;
            data = new T[2 * capacity];
            for (auto i = 0; i < size; ++i)
            {
                data[i] = tmp[i];
            }
            delete[] tmp;
            data[size] = value;
            ++size;
            capacity *= 2;
        }
        else
        {
            data[size] = value;
            ++size;
        }
    }

private:
    T *data = nullptr;
    size_t capacity = 0;
    size_t size = 0;
};