#include <iostream>
#include <deque>
#include <string>
bool HasHigherPriority(char current, char prev)
{
    if ( ( current == '*' || current == '/' ) && ( prev == '-' || prev == '+'))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
using namespace std;
struct  OPD
{
    int number;
    char op;
};
istream& operator >> (istream& is, OPD& obd)
{
    is >> obd.op;
    is >> obd.number;
    return is;
}

int main()
{
    deque<string> expression;
    int num, count;
    cin >> num >> count;
    expression.push_back(to_string(num));
    char prev ='~';
    for(int i = 0; i < count ; i++)
    {
        OPD opd;
        cin >> opd;
        if (HasHigherPriority(opd.op, prev))
        {
            expression.push_front("(");
            expression.push_back(")");
        }
        expression.push_back(" ");
        expression.push_back(string(1, opd.op));
        expression.push_back(" ");
        expression.push_back(to_string(opd.number));
        prev = opd.op;
    }
    for(const auto &chr: expression)
    {
        cout << chr;
    }
    return 0;
}