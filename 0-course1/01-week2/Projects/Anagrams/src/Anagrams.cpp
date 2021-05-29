//============================================================================
// Name        : Anagrams.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
using namespace std;

map<char, int> BuildCharCounters(const string &s) {
	map<char, int> result;
	for (auto c : s) {
		++result[c];
	}
	return result;
}

bool EqualDict(const map<char, int> &dic1, map<char, int> dic2) {
	if (dic1.size() == 0 && dic2.size() == 0) {
		return true;
	}
	if (dic1.size() == 0 || dic2.size() == 0) {
		return false;
	}
	for (auto item : dic1) {
		if (item.second != dic2[item.first]) {
			return false;
		}
	}
	return true;
}

int main() {
	unsigned int N;
	cin >> N;
	for (unsigned int i = 0; i < N; i++) {
		string s1, s2;
		cin >> s1 >> s2;
		auto dic1 = BuildCharCounters(s1);
		auto dic2 = BuildCharCounters(s2);
		if (dic1 == dic2) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}

	}
	return 0;
}
