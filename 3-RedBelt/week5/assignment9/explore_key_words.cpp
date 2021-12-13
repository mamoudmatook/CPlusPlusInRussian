#include "test_runner.h"
#include "profile.h"
#include <map>
#include <string>
#include <vector>
#include <future>
#include <set>
#include <sstream>
using namespace std;

struct Stats
{
    map<string, int> word_frequences;

    void operator+=(const Stats &other)
    {
        for (auto &[word, frequency] : other.word_frequences)
        {
            word_frequences[word] += frequency;
        }
    }
};

// Stats explore_line(const set<string> key_words, string line)
// {
//     Stats result;
//     std::stringstream ss(std::move(line));
//     std::string buf;
//     while (ss >> buf)
//     {
//         if (key_words.find(buf) != key_words.end())
//         {
//             result.word_frequences[move(buf)]++;
//         }
//     }
//     return result;
// }

Stats explore_line(const std::set<std::string> &key_words, const std::string &line)
{
    std::string_view line_view = line;
    Stats result;

    size_t pos = line_view.find_first_not_of(' ');
    line_view.remove_prefix(pos);

    while (pos != line_view.npos)
    {
        pos = line_view.find_first_of(' ');

        auto key = std::string(line_view.substr(0, pos));

        if (key_words.count(key) > 0)
        {
            ++result.word_frequences[std::move(key)];
        }

        if (pos == line_view.npos)
            break;

        line_view.remove_prefix(pos);
        pos = line_view.find_first_not_of(' ');
        line_view.remove_prefix(pos);
    }

    return result;
}

// Stats explore_segment(const set<string> &key_words, const vector<string> &segment)
// {
//     Stats result;
//     for (const string &line : segment)
//     {
//         result += explore_line(key_words, line);
//     }
//     return result;
// }

// Stats ExploreKeyWords(const set<string> &key_words, istream &input)
// {
//     Stats result;
//     vector<future<Stats> > futures;
//     const size_t max_batch_size = 5000;

//     vector<string> segment;
//     segment.reserve(max_batch_size);
//     for (string line; getline(input, line);)
//     {
//         segment.push_back(move(line));
//         if (segment.size() >= max_batch_size)
//         {
//             futures.push_back(async(explore_segment, ref(key_words), move(segment)));
//             segment.reserve(max_batch_size);
//         }
//     }
//     if (!segment.empty())
//     {
//         result += explore_segment(key_words, move(segment));
//     }
//     for (auto &f : futures)
//     {
//         result += f.get();
//     }
//     return result;
// }

// Stats ExploreKeyWords(const set<string> &key_words, istream &input)
// {
//     Stats result;
//     vector<future<Stats> > futures;
//     const auto num_threads = std::thread::hardware_concurrency();
//     vector<vector<string> > segments(num_threads);
//     int cnt = 0;
//     for (string line; getline(input, line);)
//     {
//         segments[cnt % num_threads].push_back(move(line));
//         ++cnt;
//     }

//     for (auto &segment : segments)
//     {
//         futures.push_back(async(explore_segment, ref(key_words), ref(segment)));
//     }

//     for (auto &f : futures)
//     {
//         result += f.get();
//     }
//     return result;
// }

Stats ExploreKeyWordsSingleThread(const std::set<std::string> &key_words, std::istream &input)
{
    Stats result;
    std::string line;
    while (std::getline(input, line))
    {
        result += explore_line(key_words, line);
    }

    return result;
}

Stats ExploreKeyWords(const std::set<std::string> &key_words, std::istream &input)
{
    Stats result;
    std::vector<std::future<Stats> > futures;
    size_t num_lines = 0;
    const auto num_threads = std::thread::hardware_concurrency();
    std::vector<std::stringstream> streams(num_threads);

    std::string line;
    while (std::getline(input, line))
    {
        streams[num_lines % num_threads] << line << '\n';
        ++num_lines;
    }

    for (auto &s : streams)
    {
        futures.push_back(std::async([&]
                                     { return ExploreKeyWordsSingleThread(key_words, s); }));
    }

    for (auto &future : futures)
    {
        result += future.get();
    }

    return result;
}

void TestBasic()
{
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}