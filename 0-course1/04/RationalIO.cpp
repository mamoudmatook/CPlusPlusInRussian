
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
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
int main()

{
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4")
        {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal)
        {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct)
        {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct)
        {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }
    cout << "OK" << endl;
    return 0;
}