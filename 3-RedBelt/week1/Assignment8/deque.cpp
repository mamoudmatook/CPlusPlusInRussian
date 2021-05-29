#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class Deque
{
public:
    Deque()
    {
    }
    bool Empty() const
    {
        return _front.empty() && _back.empty();
    }
    size_t Size() const
    {
        return _back.size() + _front.size();
    }
    T & operator[](size_t index)
    {
        if (index >= Size() || index < 0)
        {
            throw out_of_range("index not found");
        }
        if (index < _front.size())
        {
            index = _front.size() - index - 1;
            return _front[index];
        }
        index = index - _front.size();
        return _back[index];
    }
    const T &operator[](size_t index) const
    {
        if (index >= Size())
        {
            throw out_of_range("index not found");
        }
        if (index < _front.size())
        {
            index = _front.size() - index - 1;
            return _front[index];
        }
        index = index - _front.size();
        return _back[index];
    }
    const T& At(size_t index) const
    {
        return (*this)[index];
    }
    T& At(size_t index) 
    {
        return (*this)[index];
    }
    T &Front()
    {
        if (Empty())
        {
            throw runtime_error("Empty Deque");
        }
        if (!_front.empty())
        {
            return _front[_front.size() - 1];
        }
        return _back[0];
    }

    const T &Front() const
    {
        if (Empty())
        {
            throw runtime_error("Empty Deque");
        }
        if (!_front.empty())
        {
            return _front[_front.size() - 1];
        }
        return _back[0];
    }

    T &Back()
    {
        if (Empty())
        {
            throw runtime_error("Empty Deque");
        }
        if (!_back.empty())
        {
            return _back[_back.size() - 1];
        }
        return _front[0];
    }

    const T &Back() const
    {
        if (Empty())
        {
            throw runtime_error("Empty Deque");
        }
        if (!_back.empty())
        {
            return _back[_back.size() - 1];
        }
        return _front[0];
    }
    void PushFront(T value)
    {
        _front.push_back(value);
    }
    void PushBack(T value)
    {
        _back.push_back(value);
    }

private:
    vector<T> _front, _back;
};

// int main()
// {
//     Deque<int> d;
//     d.PushBack(3);
//     d.PushBack(4);
//     d.PushBack(5);
//     d.PushFront(10);
//     d.Front() = 12;
//     d.Back() = 30;
//     cout << d.Front() << endl;
//     cout << d.Back() << endl;
//     cout << d.Size() << endl;
//     cout << d.Empty() << endl;
//     return 0;
// }