#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string NumberToString(int Number)
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

string lookAndSay(string input) {
	int digitCount = 1;
	int inputPos = 0;

	for (int i = 0; i < input.length(); i++) {
		string num = input.substr(i, 1);
		inputPos = i;
		while (input.substr(i + 1, 1) == num) {
			digitCount++;
			i++;
		}
		i -= digitCount-2;
		input.insert(inputPos, NumberToString(digitCount));
		input.insert(inputPos + 1, num);
		input.erase(inputPos + 2, digitCount);
		digitCount = 1;
	}

	return input;
}

int main() {
	string input = "1113222113";
	int Part1 = 40;
	int Part2 = 50;


	for (int i = 0; i < Part2; i++) {
		input = lookAndSay(input);
		cout << i;
	}
	
	cout << endl;
	cout << input.length();
	cin.get();
}