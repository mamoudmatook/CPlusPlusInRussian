#include <iomanip>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <map>
#include <unordered_map>
/**
 * 
 * 
 * 
12
CHEER 5
READ 1 10
CHEER 1
READ 2 5
READ 3 7
CHEER 2
CHEER 3
READ 3 10
CHEER 3
READ 3 11
CHEER 3
CHEER 1

0
1
0
0.5
0.5
1
0.5
 * **/
using namespace std;

class ReadingManager
{
public:
    ReadingManager() {}
    void Read(int user_id, int page_count)
    {
        if (users_.count(user_id) == 0)
        {
            users_[user_id] = page_count;
            pages_[page_count] += 1;
        }
        else
        {
            auto old_page = users_.at(user_id);
            pages_[old_page] -= 1;
            users_[user_id] = page_count;
            pages_[page_count] += 1;

        }
    }

    double Cheer(int user_id) const
    {
        if (users_.count(user_id) == 0)
        {
            return 0;
        }
        if (users_.size() == 1)
        {
            return 1;
        }
        auto count = 0.0;
        auto page_nu = users_.at(user_id);
        for (auto i = page_nu - 1; i >= 0; i--)
        {
            count += pages_[i];
        }
        return count / (users_.size() - 1.0);
    }

private:
    unordered_map<int, int> users_;
    int pages_[1000] = {0};
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

    return 0;
}