#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record
{
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

class Database
{
public:
    bool Put(const Record &record)
    {
        if (id_to_record.find(record.id) != id_to_record.end())
        {
            return false;
        }
        auto [it, inserted] = id_to_record.insert({record.id, Storage{record, {}, {}, {}}});
        Storage &store = it->second;
        const Record *ptr = &store.record;
        store.time_stamp_iter = time_stamp_to_record.insert({record.timestamp, ptr});
        store.karma_iter = karma_to_record.insert({record.karma, ptr});
        store.user_iter = user_to_record.insert({record.user, ptr});
        return true;
    }
    const Record *GetById(const string &id) const
    {

        auto itr = id_to_record.find(id);
        if (itr == id_to_record.end())
        {
            return nullptr;
        }
        return &(itr->second.record);
    }
    bool Erase(const string &id)
    {

        auto itr = id_to_record.find(id);
        if (itr == id_to_record.end())
        {
            return false;
        }
        const Storage &store = itr->second;
        time_stamp_to_record.erase(store.time_stamp_iter);
        karma_to_record.erase(store.karma_iter);
        user_to_record.erase(store.user_iter);
        id_to_record.erase(itr);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        iterate_over_multi_map(low, high, time_stamp_to_record, callback);
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        iterate_over_multi_map(low, high, karma_to_record, callback);
    }

    template <typename Callback>
    void AllByUser(const string &user, Callback callback) const
    {
        if (user_to_record.find(user) != user_to_record.end())
        {
            iterate_over_multi_map(user, user, user_to_record, callback);
        }
    }

private:
    struct Storage
    {
        Record record;
        multimap<int, const Record *>::iterator time_stamp_iter;
        multimap<int, const Record *>::iterator karma_iter;
        multimap<string, const Record *>::iterator user_iter;
    };
    unordered_map<string, Storage> id_to_record;
    multimap<int, const Record *> time_stamp_to_record;
    multimap<int, const Record *> karma_to_record;
    multimap<string, const Record *> user_to_record;

    template <typename T>
    void earse_from_multimap(T key, string id, multimap<T, const Record *> &mulmap)
    {
        auto itr1 = mulmap.lower_bound(key);
        auto itr2 = mulmap.upper_bound(key);

        while (itr1 != itr2)
        {
            if (itr1->first == key && itr1->second->id == id)
            {
                mulmap.erase(itr1);
                break;
            }
            itr1++;
        }
    }
    template <typename T, typename Callback>
    void iterate_over_multi_map(const T &low, const T &high, const multimap<T, const Record *> &mulmap, Callback callback) const
    {
        auto itr1 = mulmap.lower_bound(low);
        auto itr2 = mulmap.upper_bound(high);
        while (itr1 != itr2 && callback(*(itr1->second)))
        {
            itr1++;
        }
    }
};

void TestRangeBoundaries()
{
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record &)
                    {
    ++count;
    return true; });

    ASSERT_EQUAL(2, count);
}

void TestSameUser()
{
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record &)
                 {
    ++count;
    return true; });

    ASSERT_EQUAL(2, count);
}

void TestReplacement()
{
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}