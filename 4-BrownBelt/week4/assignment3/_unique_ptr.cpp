#include "test_runner.h"

#include <cstddef>

using namespace std;

template <typename T>
class UniquePtr
{
private:
    T *t;

public:
    UniquePtr() : t(nullptr) {}
    UniquePtr(T *ptr) : t(ptr) {}
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr(UniquePtr &&other)
    {
        if (!(&other == this))
        {
            t = other.t;
            other.t = nullptr;
        }
    }
    UniquePtr &operator=(const UniquePtr &) = delete;
    UniquePtr &operator=(nullptr_t)
    {
        delete t;
        t = nullptr;
        return *this;
    }
    UniquePtr &operator=(UniquePtr &&other)
    {
        if (!(this == &other))
        {
            delete t;
            t = other.t;
            other.t = nullptr;
        }
        return *this;
    }
    ~UniquePtr()
    {
        delete t;
    }

    T &operator*() const
    {
        return *t;
    }

    T *operator->() const
    {
        return t;
    }

    T *Release()
    {
        T *tmp = t;
        t = nullptr;
        return tmp;
    }

    void Reset(T *ptr)
    {
        delete t;
        t = ptr;
    }

    void Swap(UniquePtr &other)
    {
        swap(t, other.t);
    }

    T *Get() const
    {
        return t;
    }
};

struct Item
{
    static int counter;
    int value;
    Item(int v = 0) : value(v)
    {
        ++counter;
    }
    Item(const Item &other) : value(other.value)
    {
        ++counter;
    }
    ~Item()
    {
        --counter;
    }
};

int Item::counter = 0;

void TestLifetime()
{
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters()
{
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}