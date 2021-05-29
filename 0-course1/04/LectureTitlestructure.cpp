// #include <iostream>
// #include <string>
// using namespace std;

struct Specialization
{
    string val;
    explicit Specialization(const string &s)
    {
        val = s;
    }
};

struct Course
{
    string val;
    explicit Course(const string &s)
    {
        val = s;
    }
};

struct Week
{
    string val;
    explicit Week(const string &s)
    {
        val = s;
    }
};

struct LectureTitle
{
    string specialization;
    string course;
    string week;
    LectureTitle(Specialization sp, Course crs, Week wk)
    {
        specialization = sp.val;
        course = crs.val;
        week = wk.val;
    }
};

// int main()
// {
// LectureTitle title(
// Specialization("C++"),
// Course("White belt"),
// Week("4th"));
// }