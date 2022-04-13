
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <exception>
using namespace std;

class Rational
{
public:
    Rational()
    {
        // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€ Ð¿Ð¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator)
    {
        // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€
        if (denominator == 0)
        {
            throw invalid_argument("invalid argument");
        }
        this->numerator = numerator;
        this->denominator = denominator;
        int gcd = __gcd(numerator, denominator);
        this->numerator /= gcd;
        this->denominator /= gcd;
        if (this->numerator < 0 && this->denominator < 0)
        {
            this->numerator *= -1;
            this->denominator *= -1;
        }
        else if (this->denominator < 0)
        {
            this->numerator *= -1;
            this->denominator *= -1;
        }
        else if (this->numerator == 0)
        {
            this->denominator = 1;
        }
    }

    int Numerator() const
    {
        // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
        return numerator;
    }

    int Denominator() const
    {
        // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼ÐµÑ‚Ð¾Ð´
        return denominator;
    }

private:
    // Ð”Ð¾Ð±Ð°Ð²ÑŒÑ‚Ðµ Ð¿Ð¾Ð»Ñ
    int numerator;
    int denominator;
};
bool operator==(const Rational &lhs, const Rational &rhs)
{
    if (lhs.Numerator() == rhs.Numerator())
    {
        return lhs.Denominator() == rhs.Denominator();
    }
    return false;
}
Rational operator+(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator-(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator/(const Rational &lhs, const Rational &rhs)
{
    if (rhs.Numerator() == 0)
    {
        throw domain_error("domain error");
    }
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}
Rational operator*(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}
istream &operator>>(istream &input, Rational &r)
{

    int num, denom;
    char symbol;
    if (input >> num >> symbol >> denom)
    {
        if (symbol == '/')
        {
            r = Rational(num, denom);
        }
    }
    return input;
}
ostream &operator<<(ostream &output, const Rational &r)
{
    output << r.Numerator() << "/" << r.Denominator();
    return output;
}
bool operator<(const Rational &lhs, const Rational &rhs)
{
    return (lhs - rhs).Numerator() < 0;
}
int main()
{
    try
    {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument &)
    {
    }

    try
    {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error &)
    {
    }

    cout << "OK" << endl;
    return 0;
}