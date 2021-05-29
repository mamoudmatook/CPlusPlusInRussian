/* 
** Refactoring
** Artem Barinov
** March 12, 2021
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
    public:
    Person(const string& name, const string& prof) : name_(name), prof_(prof) {}
    // uznaem kak zvat'
    string getName() const { 
        return name_; 
    }
    // uznaem kto po jizni
    string getStatus() const { 
        return prof_; 
    }
    // esli ne umeet hodit' - nau4im
    virtual void Walk(const string& destination) const {
        cout << getStatus() << ": " << getName() << " walks to: " << destination << endl;        
    }
    // 4tobi ne zaglyadivali vsyakie
    private:
    string name_;
    string prof_;
};

class Student : public Person {
    public:    
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong){}
    
    void Learn() const {
        cout << "Student: " << getName() << " learns" << endl;
    }
    // etot samostoyatelno hodit i poet
    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }
    void SingSong() const {
        cout << "Student: " << getName() << " sings a song: " << FavouriteSong << endl;
    }

    protected:    
    string FavouriteSong;
};


class Teacher : public Person {
    public:
    Teacher(string name, string subject) : Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << "Teacher: " << getName() << " teaches: " << Subject << endl;
    }

    public:    
    string Subject;
};


class Policeman : public Person {
    public:
    Policeman(const string& name) : Person(name, "Policeman"){}

    void Check(Person& person) const {
        cout << "Policeman: " << getName() << " checks " << person.getStatus() <<". " << person.getStatus() << "'s name is: " << person.getName() << endl;
    }   
};


void VisitPlaces(Person& p, vector<string> places) {
    for (auto i : places) {
        p.Walk(i);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}