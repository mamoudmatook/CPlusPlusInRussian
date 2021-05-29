#include <iostream>
#include <string>
using namespace std;
class A
{
public:
    A(const string &st) : type_(st) {}
    void sound() const
    {
        cout << "A class" << endl;
    }

private:
    string type_;
};

class B : public A
{
public:
    B(const string &st) : A(st) {}
    void sound() const
    {
        cout << "B class" << endl;
    }
};

void MakeSound(const A &a) 
{
    a.sound();
}

int main()
{
    B b("Class b");
    MakeSound(b);
}