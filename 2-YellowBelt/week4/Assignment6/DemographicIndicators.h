#pragma once
#include <vector>
#include <algorithm>
using namespace std;
enum class Gender
{
    FEMALE,
    MALE
};
struct Person
{
    int age;          // возраст
    Gender gender;    // пол
    bool is_employed; // имеет ли работу
};
void PrintStats(vector<Person> persons);
