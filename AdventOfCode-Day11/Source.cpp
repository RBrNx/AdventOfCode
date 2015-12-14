#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string incrementPassword(string input, int pos) {
	char lastChar = input.at(pos);

	if (lastChar != 'z') {
		lastChar++;
		input.erase(pos, 1);
		input.insert(pos, 1, lastChar);
	}
	else {
		lastChar = 'a';
		input.erase(pos, 1);
		input.insert(pos, 1, lastChar);
		return incrementPassword(input, pos - 1);
	}
	return input;
}

bool testPassword(string input) {
	//Check for confusing letter
	int confusingLetter = 0;
	if ((confusingLetter = input.find("i")) > 0 || (confusingLetter = input.find("o")) > 0 || (confusingLetter = input.find("l")) > 0) {
		return false;
	}
	
	//Check for more than 1 differnt double letter
	vector<string> doubleLetters;
	for (int j = 0; j < input.length() - 1; j++) {
		if (input.at(j) == input.at(j + 1)) {
			string Double;
			Double.insert(0, 1, input.at(j));
			Double.insert(1, 1, input.at(j+1));
			if (find(doubleLetters.begin(), doubleLetters.end(), Double) != doubleLetters.end()) {
				return false;
			}
			else {
				doubleLetters.push_back(Double);
				j++;
			}
			
		}

	}
	if (doubleLetters.size() < 2) {
		return false;
	}

	char Letter;
	bool increasingFound = false;
	//Check for increasing straight of 3 letters
	for (int i = 0; i < input.length() - 2; i++) {
		Letter = input.at(i);
		if (input.at(i + 1) == (Letter+=1)) {
			Letter = input.at(i + 1);
			if (input.at(i + 2) == (Letter+=1)) {
				increasingFound = true;
			}
		}
	}
	if (!increasingFound) {
		return false;
	}

	return true;
}

int main() {
	string input = "vzbxkghb";
	string input2 = "vzbxxyzz";
	bool securePassword = false;

	while (securePassword == false) {
		input2 = incrementPassword(input2, input2.length()-1);
		securePassword = testPassword(input2);
	}

	cout << input2;

	cin.get();
}

