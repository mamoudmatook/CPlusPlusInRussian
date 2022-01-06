#include "test_runner.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

using namespace std;

struct HttpRequest
{
    string method, path, body;
    map<string, string> get_params;
};

pair<string, string> SplitBy(const string &what, const string &by)
{
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size())
    {
        return {what.substr(0, pos), what.substr(pos + by.size())};
    }
    else
    {
        return {what, {}};
    }
}

template <typename T>
T FromString(const string &s)
{
    T x;
    istringstream is(s);
    is >> x;
    return x;
}

pair<size_t, string> ParseIdAndContent(const string &body)
{
    auto [id_string, content] = SplitBy(body, " ");
    return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo
{
    size_t user_id, consecutive_count;
};

struct HttpHeader
{
    string name, value;
};

ostream &operator<<(ostream &output, const HttpHeader &h)
{
    return output << h.name << ": " << h.value;
}

enum class HttpCode
{
    Ok = 200,
    NotFound = 404,
    Found = 302,
};
ostream &operator<<(ostream &output, HttpCode code)
{
    switch (code)
    {
    case HttpCode::Ok:
        output << "200 OK";
        break;
    case HttpCode::Found:
        output << "302 Found";
        break;
    case HttpCode::NotFound:
        output << "404 Not found";
        break;
    default:
        throw invalid_argument("Unknown code");
    }
    return output;
}

class HttpResponse
{
public:
    explicit HttpResponse(HttpCode code) : code_(code) {}

    HttpResponse &AddHeader(string name, string value)
    {
        headers_.push_back({move(name), move(value)});
        return *this;
    }
    HttpResponse &SetContent(string a_content)
    {
        content_ = move(a_content);
        return *this;
    }
    HttpResponse &SetCode(HttpCode a_code)
    {
        code_ = a_code;
        return *this;
    }

    friend ostream &operator<<(ostream &output, const HttpResponse &resp)
    {
        output << "HTTP/1.1 " << resp.code_ << '\n';
        for (const auto &header : resp.headers_)
        {
            output << header << "\n";
        }
        if (!resp.content_.empty())
        {
            output << "Content-Length: " << resp.content_.size() << '\n';
        }
        output << '\n'
               << resp.content_;
        return output;
    }

private:
    HttpCode code_;
    vector<HttpHeader> headers_;
    string content_;
};

class CommentServer
{
private:
    vector<vector<string> > comments_;
    std::optional<LastCommentInfo> last_comment;
    unordered_set<size_t> banned_users;

public:
    HttpResponse ServeRequest(const HttpRequest &req)
    {
        if (req.method == "POST")
        {
            if (req.path == "/add_user")
            {
                comments_.emplace_back();
                return HttpResponse(HttpCode::Ok).SetContent(to_string(comments_.size() - 1));
            }
            else if (req.path == "/add_comment")
            {
                auto [user_id, comment] = ParseIdAndContent(req.body);

                if (!last_comment || last_comment->user_id != user_id)
                {
                    last_comment = LastCommentInfo{user_id, 1};
                }
                else if (++last_comment->consecutive_count > 3)
                {
                    banned_users.insert(user_id);
                }

                if (banned_users.count(user_id) == 0)
                {
                    comments_[user_id].push_back(string(comment));
                    return HttpResponse(HttpCode::Ok);
                }
                else
                {
                    return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
                }
            }
            else if (req.path == "/checkcaptcha")
            {
                if (auto [id, response] = ParseIdAndContent(req.body); response == "42")
                {
                    banned_users.erase(id);
                    if (last_comment && last_comment->user_id == id)
                    {
                        last_comment.reset();
                    }
                    return HttpResponse(HttpCode::Ok);
                }
                else
                {
                    return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
                }
            }
            else
            {
                return HttpResponse(HttpCode::NotFound);
            }
        }
        else if (req.method == "GET")
        {
            if (req.path == "/user_comments")
            {
                auto user_id = FromString<size_t>(req.get_params.at("user_id"));
                string response;
                for (const string &c : comments_[user_id])
                {
                    response += c + '\n';
                }
                return HttpResponse(HttpCode::Ok).SetContent(move(response));
            }
            else if (req.path == "/captcha")
            {
                return HttpResponse(HttpCode::Ok).SetContent("What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
            }
            else
            {
                return HttpResponse(HttpCode::NotFound);
            }
        }
        else
        {
            return HttpResponse(HttpCode::NotFound);
        }
    }
};