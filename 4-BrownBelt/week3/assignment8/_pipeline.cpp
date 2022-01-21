#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email
{
    string from;
    string to;
    string body;
};

class Worker
{
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run()
    {
        throw logic_error("Unimplemented");
    }

protected:
    void PassOn(unique_ptr<Email> email) const
    {
        if (next_)
            next_->Process(move(email));
    }

public:
    void SetNext(unique_ptr<Worker> next)
    {
        next_ = move(next);
    }
    unique_ptr<Worker> next_;
};

class Reader : public Worker
{
public:
    explicit Reader(istream &in) : is(in) {}
    void Process(unique_ptr<Email> email) override {}
    void Run() override
    {
        for (;;)
        {
            auto email = make_unique<Email>();
            getline(is, email->from);
            getline(is, email->to);
            getline(is, email->body);
            if (is)
            {
                PassOn(move(email));
            }
            else
            {
                break;
            }
        }
    }

private:
    istream &is;
};

class Filter : public Worker
{
public:
    using Function = function<bool(const Email &)>;
    explicit Filter(Function func) : func_(move(func)) {}
    void Process(unique_ptr<Email> email) override
    {
        if (func_(*email))
        {
            PassOn(move(email));
        }
    }

public:
    Function func_;
};

class Copier : public Worker
{
public:
    explicit Copier(string recp) : recp_(move(recp)) {}
    void Process(unique_ptr<Email> email) override
    {
        if (email->to != recp_)
        {
            auto new_recp = make_unique<Email>(*email);
            new_recp->to = recp_;
            PassOn(move(email));
            PassOn(move(new_recp));
        }
        else
            PassOn(move(email));
    }

private:
    string recp_;
};

class Sender : public Worker
{
public:
    explicit Sender(ostream &os) : os_(os) {}
    void Process(unique_ptr<Email> email) override
    {
        os_ << email->from << endl
            << email->to << endl
            << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream &os_;
};

class PipelineBuilder
{
public:
    explicit PipelineBuilder(istream &in)
    {
        workers.push_back(make_unique<Reader>(in));
    }

    PipelineBuilder &FilterBy(Filter::Function filter)
    {
        workers.push_back(make_unique<Filter>(move(filter)));
        return *this;
    }

    PipelineBuilder &CopyTo(string recipient)
    {
        workers.push_back(make_unique<Copier>(recipient));
        return *this;
    }

    PipelineBuilder &Send(ostream &out)
    {
        workers.push_back(make_unique<Sender>(out));
        return *this;
    }

    unique_ptr<Worker> Build()
    {
        for (int i = workers.size() - 1; i > 0; --i)
        {
            workers[i - 1]->SetNext(move(workers[i]));
        }
        return move(workers[0]);
    }

private:
    vector<unique_ptr<Worker> > workers;
};

void TestSanity()
{
    string input = ("erich@example.com\n"
                    "richard@example.com\n"
                    "Hello there\n"

                    "erich@example.com\n"
                    "ralph@example.com\n"
                    "Are you sure you pressed the right button?\n"

                    "ralph@example.com\n"
                    "erich@example.com\n"
                    "I do not make mistakes of that kind\n");
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email)
                     { return email.from == "erich@example.com"; });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = ("erich@example.com\n"
                             "richard@example.com\n"
                             "Hello there\n"

                             "erich@example.com\n"
                             "ralph@example.com\n"
                             "Are you sure you pressed the right button?\n"

                             "erich@example.com\n"
                             "richard@example.com\n"
                             "Are you sure you pressed the right button?\n");

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}