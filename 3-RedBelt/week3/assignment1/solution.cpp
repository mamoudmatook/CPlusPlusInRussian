#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool
{
public:
    T *Allocate()
    {
        T *ob;
        if (released.size() == 0)
        {
            ob = new T;
            allocated.insert(ob);
        }
        else
        {
            ob = released.front();
            allocated.insert(ob);
            released.pop();
        }
        return ob;
    }
    T *TryAllocate()
    {
        if (released.size() == 0)
        {
            return nullptr;
        }
        else
        {
            return Allocate();
        }
    }

    void Deallocate(T *object)
    {
        if (allocated.find(object) != allocated.end())
        {
            released.push(object);
            allocated.erase(allocated.find(object));
        }
        else
        {
            throw invalid_argument("No object!");
        }
    }

    ~ObjectPool()
    {
        while (!released.empty())
        {
            auto t = released.front();
            delete t;
            released.pop();
        }
        for (auto e : allocated)
        {
            delete e;
        }
        allocated.clear();
    }

private:
    queue<T *> released;
    set<T *> allocated;
};

void TestObjectPool()
{
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}