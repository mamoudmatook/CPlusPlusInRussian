#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

// class Rational
// {
// public:

//     Rational();
//     Rational(int numerator, int denominator)
//     {
//     }

//     int Numerator() const
//     {
//     }

//     int Denominator() const
//     {
//     }
// };

void TestRationalCalss()
{
    // default constructor
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);

    //irreducabile fractions
    Rational r5(3,10); 
    AssertEqual(r5.Numerator(), 3);
    AssertEqual(r5.Denominator(), 10);
    Rational r8(1, 1);
    AssertEqual(r8.Numerator(), 1);
    AssertEqual(r8.Denominator(), 1);

    //reduced fractions
    Rational r1(5,15); 
    AssertEqual(r1.Numerator(), 1);
    AssertEqual(r1.Denominator(), 3);
    Rational r15(2,4); 
    AssertEqual(r15.Numerator(), 1);
    AssertEqual(r15.Denominator(), 2);

    // negative denominator
    Rational r2(5,-15); 
    AssertEqual(r2.Numerator(), -1);
    AssertEqual(r2.Denominator(), 3);

    //negative numerator
    Rational r6(-4,6); 
    AssertEqual(r6.Numerator(), -2);
    AssertEqual(r6.Denominator(), 3);

    // both negative
    Rational r3(-5,-15); 
    AssertEqual(r3.Numerator(), 1);
    AssertEqual(r3.Denominator(), 3);
    Rational r11(-3,-4); 
    AssertEqual(r11.Numerator(), 3);
    AssertEqual(r11.Denominator(), 4);

    // numerator equal to zero
    Rational r4(0,15); 
    AssertEqual(r4.Numerator(), 0);
    AssertEqual(r4.Denominator(), 1);

   // limits of int 
    Rational r7(numeric_limits<int>::max(),numeric_limits<int>::max());
    AssertEqual(r7.Numerator(), 1);
    AssertEqual(r7.Denominator(), 1);
    Rational r10(numeric_limits<int>::min(), numeric_limits<int>::min());
    AssertEqual(r10.Numerator(), 1);
    AssertEqual(r10.Denominator(), 1);

}
int main()
{
    TestRunner runner;
    runner.RunTest(TestRationalCalss, "TestRationalCalss");
    return 0;
}