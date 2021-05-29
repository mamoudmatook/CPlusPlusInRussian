//============================================================================
// Name        : DirectoryOfCapitals.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
 Implement a directory of country capitals.

The program receives the following requests at the entrance:

CHANGE_CAPITAL country new_capital - changing the capital of the country country to new_capital , or adding such a country with such a capital, if it did not exist before.
RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
ABOUT country - displays the capital of the country .
DUMP - display of capitals of all countries.
Input format
The first line contains the number of queries Q , the next Q lines contain the descriptions of the queries. All names of countries and capitals consist only of Latin letters, numbers and underscores.

Output format
Print the result of processing each request:

In response to the CHANGE_CAPITAL request country new_capital print
New country Introduce country with Capital new_capital , if the country's country did not exist;
Country country hasn't changed its capital , if the country of the country had a new_capital capital until now ;
Country country has changed its capital from old_capital to new_capital , if the country of the country until now had the capital of old_capital , the name of which does not coincide with the name of new_capital .
In response to the RENAME old_country_name new_country_name query, output
Incorrect rename, skip , if the new country name matches the old one, the country old_country_name does not exist, or the country new_country_name already exists;
Country old_country_name with capital capital has been renamed to new_country_name if the request is correct and the country has capital capital .
In response to the request for ABOUT country, print
Country country doesn't exist if the country named country doesn't exist;
Country country has capital capital if the country country exists and has capital capital .
In response to the DUMP query , output
There are no countries in the world , if no country has been added yet;
a sequence of country / capital pairs describing the capitals of all countries, if there is already at least one country in the world. When displaying a sequence, pairs of the specified type must be sorted by country name and separated by a space.

 */

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	int Q;
	map<string, string> countries;
	cin >> Q;
	for (int i =0; i < Q; i++) {
		string command;
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			string country, capital;
			cin >> country >> capital;
			if (countries.find(country) == countries.end()) {
				countries[country] = capital;
				cout << "Introduce new country " << country << " with capital " << capital << endl;
			} else if(countries[country] == capital) {
				cout << "Country " << country << " hasn't changed its capital" << endl;
			} else {
				auto old_capital = countries[country];
				countries[country] = capital;
				cout << "Country " << country << " has changed its capital from "<< old_capital << " to " << capital << endl;
			}

		} else if (command == "RENAME") {
			string old_name, new_name;
			cin >> old_name >> new_name;
			if (old_name == new_name || countries.find(old_name) == countries.end() || countries.find(new_name) != countries.end()) {
				cout << "Incorrect rename, skip" << endl;
			} else {
				if (countries.find(old_name) != countries.end()) {
					auto capital = countries[old_name];
					countries.erase(old_name);
					countries[new_name] = capital;
					cout << "Country " << old_name << " with capital " <<  capital << " has been renamed to " << new_name << endl;
				}
			}

		} else if (command == "ABOUT") {
			string country;
			cin >> country;
			if (countries.find(country) == countries.end()) {
				cout << "Country " << country <<  " doesn't exist" << endl;
			} else {
				cout << "Country " << country <<  " has capital " << countries[country] << endl;
			}

		} else {
			if (countries.size() == 0) {
				cout << "There are no countries in the world" << endl;
			} else {
				for (auto country : countries) {
					cout << country.first <<"/" << country.second << " ";
				}
				cout << endl;
			}

		}
	}

	return 0;
}
