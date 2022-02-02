#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>

using namespace std;

class ReadingManager
{
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count)
    {
        if (users_.find(user_id) == users_.end())
        {
            users_[user_id] = page_count;
            pages_.insert(page_count);
        }
        else
        {
            int page = users_[user_id];
            pages_.erase(pages_.lower_bound(page));
            users_[user_id] = page_count;
            pages_.insert(page_count);
        }
    }

    double Cheer(int user_id) const
    {
        if (users_.count(user_id) == 0)
            return 0.0;
        if (pages_.size() == 1)
            return 1.0;
        int page_count = users_.at(user_id);
        auto it = pages_.lower_bound(page_count);
        double size = distance(pages_.begin(), it);
        return size / (pages_.size() - 1);
    }

private:
    unordered_map<int, int> users_;
    multiset<int> pages_;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ReadingManager manager;

    int query_count;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER")
        {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    // cout << manager.Cheer(5) << endl;
    // manager.Read(1, 10);
    // cout << manager.Cheer(1) << endl;
    // manager.Read(2, 5);
    // manager.Read(3, 7);
    // cout << manager.Cheer(2) << endl;
    // cout << manager.Cheer(3) << endl;
    // manager.Read(3, 10);
    // cout << manager.Cheer(3) << endl;
    // manager.Read(3, 11);
    // cout << manager.Cheer(3) << endl;
    // cout << manager.Cheer(1) << endl;
    return 0;
}