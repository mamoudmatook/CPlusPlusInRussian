#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector
{
public:
    SimpleVector()
    {
    }
    explicit SimpleVector(size_t size)
    {
        arr = new T[size];
        capacity_ = size;
        _size = size;
    }
    ~SimpleVector()
    {
        delete[] arr;
    }

    T &operator[](size_t index)
    {
        return arr[index];
    }

    const T &operator[](size_t index) const
    {
        return arr[index];
    }

    T *begin()
    {
        return arr;
    }

    const T *begin() const
    {
        return arr;
    }

    T *end()
    {
        return arr + _size;
    }
    const T *end() const
    {
        return arr + _size;
    }
    size_t Size() const
    {
        return _size;
    }
    size_t Capacity() const
    {
        return capacity_;
    }
    void PushBack(const T &value)
    {
        if (arr == nullptr)
        {
            arr = new T[1];
            arr[_size] = value;
            ++_size;
            capacity_ = 1;
        }
        else if (_size == capacity_)
        {
            T *tmp = new T[_size];
            for (auto i = 0; i < _size; ++i)
            {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = new T[2 * capacity_];
            for (auto i = 0; i < _size; ++i)
            {
                arr[i] = tmp[i];
            }
            delete [] tmp;
            arr[_size] = value;
            ++_size;
            capacity_ *= 2;
        }
        else
        {
            arr[_size] = value;
            ++_size;
        }
    }

private:
    T *arr = nullptr;
    size_t capacity_ = 0;
    size_t _size = 0;
};