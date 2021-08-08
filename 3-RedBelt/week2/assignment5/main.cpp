#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;
struct booking
{
    long int time;
    string hotel_name;
    int client_id;
    unsigned int room_count;
};

class BookingManager
{
public:
    long int current_time_;
    static const int sec_per_day_ = 86400;
    queue<booking> bookings_;
    unordered_map<string, unordered_set<int> > hotels_to_clients;
    unordered_map<string, int> hotels_to_rooms;
    void deleter(const long int &time, const string &hotel_name, const int &client_id, const unsigned int &room_count);
    void inserter(const long int &time, const string &hotel_name, const int &client_id, const unsigned int &room_count);

    void Book(const long int &time, const string &hotel_name, const int &client_id, const unsigned int &room_count);
    unsigned int Cliens(const string &hotel_name);
    unsigned int Rooms(const string &hotel_name);
    BookingManager(/* args */);
    ~BookingManager();
};

BookingManager::BookingManager(/* args */) : current_time_(0) {}
BookingManager::~BookingManager() {}
void BookingManager::Book(const long int &time, const string &hotel_name, const int &client_id,
                          const unsigned int &room_count)
{
    current_time_ = time;
    if (bookings_.empty())
    {
        inserter(time, hotel_name, client_id, room_count);
    }
    else
    {
        deleter(time, hotel_name, client_id, room_count);
        inserter(time, hotel_name, client_id, room_count);
    }
}

unsigned int BookingManager::Cliens(const string &hotel_name)
{
    if (hotels_to_clients.count(hotel_name) == 0)
    {
        return 0;
    }
    else
    {
        return hotels_to_clients.at(hotel_name).size();
    }
}

unsigned int BookingManager::Rooms(const string &hotel_name)
{
    if (hotels_to_rooms.count(hotel_name) == 0)
    {
        return 0;
    }
    else
    {
        return hotels_to_rooms.at(hotel_name);
    }
}

void BookingManager::inserter(const long int &time, const string &hotel_name, const int &client_id, const unsigned int &room_count)
{
    bookings_.push({time, hotel_name, client_id, room_count});
    hotels_to_clients[hotel_name].insert(client_id);
    hotels_to_rooms[hotel_name] += room_count;
}
void BookingManager::deleter(const long int &time, const string &hotel_name, const int &client_id, const unsigned int &room_count)
{
    while (!bookings_.empty())
    {  
        booking book = bookings_.front();
        if (current_time_ - book.time >= sec_per_day_)
        {
            hotels_to_clients.at(book.hotel_name).erase(book.client_id);
            hotels_to_rooms.at(book.hotel_name) -= book.room_count;
            bookings_.pop();
        }
        else
        {
            break;
        }
    }
}
int main()
{
    BookingManager booker;
    int query_count;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK")
        {
            long int time;
            string hotel_name;
            int client_id;
            unsigned room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            booker.Book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << booker.Cliens(hotel_name) << endl;
        }
        else if (query_type == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << booker.Rooms(hotel_name) << endl;
        }
    }
    return 0;
}