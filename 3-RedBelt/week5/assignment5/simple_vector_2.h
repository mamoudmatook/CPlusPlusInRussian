#pragma once
#include <cstdint>
#include <algorithm>
#include <cstdlib>

using namespace std;
template <typename T>
class SimpleVector
{
public:
    SimpleVector()
    {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
    explicit SimpleVector(size_t size)
    {
        capacity_ = 2 * size;
        data_ = new T[capacity_];
        size_ = size;
    }
    SimpleVector(const SimpleVector &rhs) : data_(new T[rhs.capacity_]),
                                            size_(rhs.size_), capacity_(rhs.capacity_)
    {
        copy(rhs.begin(), rhs.end(), begin());
    }
    SimpleVector(SimpleVector &&rhs) : data_(rhs.data_),
                                            size_(rhs.size_), capacity_(rhs.capacity_)
    {
        rhs.data_ = nullptr;
        rhs.capacity_ = rhs.size_ = 0;
    }
    SimpleVector<T> &operator=(const SimpleVector &rhs)
    {
        delete[] data_;
        data_ = new T[rhs.size_];
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        copy(rhs.begin(), rhs.end(), begin());
        return *this;
    }
    SimpleVector<T> &operator=(SimpleVector &&rhs)
    {
        delete[] data_;
        data_ = rhs.data_;
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        rhs.data_ = nullptr;
        rhs.capacity_ = rhs.size_ = 0;
        return *this;
    }
    ~SimpleVector()
    {
        delete[] data_;
    }

    T &operator[](size_t index)
    {
        return data_[index];
    }

    const T &operator[](size_t index) const
    {
        return data_[index];
    }

    T *begin()
    {
        return data_;
    }

    const T *begin() const
    {
        return data_;
    }

    T *end()
    {
        return data_ + size_;
    }
    const T *end() const
    {
        return data_ + size_;
    }
    size_t Size() const
    {
        return size_;
    }
    size_t Capacity() const
    {
        return capacity_;
    }
    void PushBack(const T &value)
    {
        if (data_ == nullptr)
        {
            data_ = new T[1];
            data_[size_] = value;
            ++size_;
            capacity_ = 1;
        }
        else if (size_ == capacity_)
        {
            T *tmp = new T[size_];
            for (auto i = 0; i < size_; ++i)
            {
                tmp[i] = data_[i];
            }
            delete[] data_;
            data_ = new T[2 * capacity_];
            for (auto i = 0; i < size_; ++i)
            {
                data_[i] = tmp[i];
            }
            delete[] tmp;
            data_[size_] = value;
            ++size_;
            capacity_ *= 2;
        }
        else
        {
            data_[size_] = value;
            ++size_;
        }
    }

    void PushBack(T &&value)
    {
        if (data_ == nullptr)
        {
            data_ = new T[1];
            data_[size_] = move(value);
            ++size_;
            capacity_ = 1;
        }
        else if (size_ == capacity_)
        {
            T *tmp = new T[size_];
            for (auto i = 0; i < size_; ++i)
            {
                tmp[i] = move(data_[i]);
            }
            delete[] data_;
            data_ = new T[2 * capacity_];
            for (auto i = 0; i < size_; ++i)
            {
                data_[i] = move(tmp[i]);
            }
            delete[] tmp;
            data_[size_] = move(value);
            ++size_;
            capacity_ *= 2;
        }
        else
        {
            data_[size_] = move(value);
            ++size_;
        }
    }

private:
    T *data_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
};