#include <iostream>
template <typename T>
class SimpleVector
{
private:
    T *data;
    T *end_;

public:
    SimpleVector(size_t size)
    {
        data = new T[size];
        end_ = data + size;
    }
    const T *begin() const
    {
        return data;
    }
    const T *end() const
    {
        return end_;
    }
    T &operator[](size_t index)
    {
        return data[index];
    }
    ~SimpleVector()
    {
        delete[] data;
    }
};

int main()
{
    SimpleVector<int> simple(5);
    simple[0] = 3;
    std::cout << simple[1] << std::endl;
}