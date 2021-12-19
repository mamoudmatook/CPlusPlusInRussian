#include "test_runner.h"

#include <forward_list>
#include <iterator>
#include <vector>

using namespace std;

template <typename Type, typename Hasher>
class HashSet
{
public:
    using BucketList = forward_list<Type>;

public:
    explicit HashSet(
        size_t num_buckets,
        const Hasher &hasher_ = {})
    {
        data = vector<BucketList>(num_buckets);
        hasher = hasher_;
    }

    void Add(const Type &value)
    {
        const size_t idx = hasher(value) % data.size();
        if (data[idx].empty())
        {
            data[idx].push_front(value);
        }
        else
        {
            auto itr = data[idx].begin();
            for (; itr != data[idx].end();)
            {
                if (*itr == value)
                {
                    return;
                }
                if (next(itr) == data[idx].end())
                {
                    break;
                }
                itr = next(itr);
            }
            data[idx].insert_after(itr, value);
        }
    }
    bool Has(const Type &value) const
    {
        const size_t idx = hasher(value) % data.size();
        auto itr = data[idx].begin();
        for (; itr != data[idx].end();)
        {
            if (*itr == value)
            {
                return true;
            }
            itr = next(itr);
        }
        return false;
    }
    void Erase(const Type &value)
    {
        const size_t idx = hasher(value) % data.size();
        if (data[idx].empty())
        {
            return;
        }
        auto itr = data[idx].begin();
        if (*itr == value)
        {
            data[idx].erase_after(data[idx].before_begin());
            return;
        }
        for (; itr != data[idx].end();)
        {
            if (*next(itr) == value)
            {
                break;
            }
            itr = next(itr);
        }
        if (itr == data[idx].end())
        {
            return;
        }
        data[idx].erase_after(itr);
    }
    const BucketList &GetBucket(const Type &value) const
    {
        return data.at(hasher(value) % data.size());
    }

private:
    vector<BucketList> data;
    Hasher hasher;
};

struct IntHasher
{
    size_t operator()(int value) const
    {
        return value;
    }
};

struct TestValue
{
    int value;

    bool operator==(TestValue other) const
    {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher
{
    size_t operator()(TestValue value) const
    {
        return value.value / 2;
    }
};

void TestSmoke()
{
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT(!hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(hash_set.Has(5));
}

void TestEmpty()
{
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value)
    {
        ASSERT(!hash_set.Has(value));
    }
}

void TestIdempotency()
{
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
}

void TestEquivalence()
{
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    ASSERT(hash_set.Has(TestValue{2}));
    ASSERT(hash_set.Has(TestValue{3}));

    const auto &bucket = hash_set.GetBucket(TestValue{2});
    const auto &three_bucket = hash_set.GetBucket(TestValue{3});
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestEquivalence);
    return 0;
}