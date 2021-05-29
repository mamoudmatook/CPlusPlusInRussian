#include <iostream>

using namespace std;

class Animal
{
public:
    Animal(const string &st) : Name(st)
    {}
    // ваш код

    const string Name;
};

class Dog: public Animal
{
public:
    Dog(const string &st): Animal(st) {}

    void Bark()
    {
        cout << Name << " barks: woof!" << endl;
    }
};