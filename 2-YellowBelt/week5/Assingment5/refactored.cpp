#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class Person
{
public:
    Person(const string &name, const string job) : _Name(name), _job(job) {}
    virtual string Name() const = 0;
    virtual void Walk(const string &destination) const = 0;
    virtual string Job() const = 0;
    string _Name;
    string _job;
};

class Student : public Person
{
public:
    Student(const string &name, const string &favouriteSong): Person(name, "Student"), _FavouriteSong(favouriteSong){}
    string Name() const override
    {
        return _Name;
    }
    string Job() const override
    {
        return _job;
    }
    void Learn()
    {
        cout << "Student: " << _Name << " learns" << endl;
    }

    void Walk(const string &destination) const override
    {
        cout << "Student: " << _Name << " walks to: " << destination << endl;
        cout << "Student: " << _Name << " sings a song: " << _FavouriteSong << endl;
    }

    void SingSong()
    {
        cout << "Student: " << _Name << " sings a song: " << _FavouriteSong << endl;
    }

public:
    string _FavouriteSong;
};

class Teacher: public Person
{
public:
    Teacher(const string &name, const string &subject): Person(name, "Teacher"), _Subject(subject){}

    void Teach()
    {
        cout << "Teacher: " << _Name << " teaches: " << _Subject << endl;
    }

    void Walk(const string &destination) const override
    {
        cout << "Teacher: " << _Name << " walks to: " << destination << endl;
    }
    string Name() const override
    {
        return _Name;
    }
    string Job() const override
    {
        return _job;
    }

public:
    string _Subject;
};

class Policeman : public Person
{
public:
    Policeman(string name): Person(name, "Policeman"){}

    void Check(const shared_ptr <Person> &person) const
    {
        cout << "Policeman: " << _Name << " checks " << person -> Job() <<". " << person -> Job() << "'s name is: " << person -> Name() << endl;
    }

    void Walk(const string &destination) const override
    {
        cout << "Policeman: " << _Name << " walks to: " << destination << endl;
    }
    string Name() const override
    {
        return _Name;
    }
    string Job() const override
    {
        return _job;
    }
};

void VisitPlaces( const shared_ptr<Person>  &person, vector<string> places)
{
    for (auto p : places)
    {
        person -> Walk(p);
    }
}

int main()
{
    auto t = make_shared<Teacher>("Jim", "Math");
    auto s = make_shared <Student> ("Ann", "We will rock you");
    auto p = make_shared <Policeman>("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p -> Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
