#include "Common.h"
#include <mutex>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;

class LruCache : public ICache
{
public:
    LruCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const Settings &settings) : unpacker_(move(books_unpacker)),
                                    settings_(settings)
    {
    }

    BookPtr GetBook(const string &book_name) override
    {
        lock_guard<mutex> gurad(mtx_);
        auto it = cache_.find(book_name);
        if (it == cache_.end())
        {
            auto book = unpacker_->UnpackBook(book_name);
            auto book_size = book->GetContent().size();
            while (!cache_.empty() && book_size + current_size > settings_.max_memory)
            {
                remove_book();
            }
            assert(!cache_.empty() || current_size == 0);
            if (book_size > settings_.max_memory)
            {
                return move(book);
            }
            current_size += book_size;
            auto p = cache_.insert({book_name, make_pair(move(book), current_rank + 1)});
            return p.first->second.first;
        }
        else
        {
            it->second.second = current_rank + 1;
            return it->second.first;
        }
    }

private:
    Settings settings_;
    unsigned int current_rank = 0;
    size_t current_size = 0;
    mutex mtx_;
    unordered_map<string, pair<BookPtr, unsigned int> > cache_;
    shared_ptr<IBooksUnpacker> unpacker_;
    void remove_book()
    {
        assert(!cache_.empty());
        auto it = min_element(cache_.begin(), cache_.end(),
                              [](decltype(cache_)::value_type &l, decltype(cache_)::value_type &r) -> bool
                              { return l.second.second < r.second.second; });
        current_size -= it->second.first->GetContent().size();
        cache_.erase(it);
    }
};

unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings &settings)
{
    return make_unique<LruCache>(books_unpacker, settings);
}