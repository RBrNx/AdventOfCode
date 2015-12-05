#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

bool naughtyOrNice(string word) {
	int vowelCount = 0;
	bool doubleLetter = false;
	int stringFound = 0;

	for (int i = 0; i < word.length(); i++) {
		if (word.at(i) == 'a' || word.at(i) == 'e' || word.at(i) == 'i' || word.at(i) == 'o' || word.at(i) == 'u') {
			vowelCount++;
		}
	}
	if (vowelCount >= 3) {
		for (int j = 0; j < word.length()-1; j++) {
			if (word.at(j) == word.at(j + 1)) {
				doubleLetter = true;
			}
		}
	}
	if (doubleLetter == true) {
		if ((stringFound = word.find("ab")) == string::npos) {
			if ((stringFound = word.find("cd")) == string::npos) {
				if ((stringFound = word.find("pq")) == string::npos) {
					if ((stringFound = word.find("xy")) == string::npos) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool naughtyOrNice2(string word) {
	bool repeatingLetter = false;
	int pairCount = 0;
	int pairCount2 = 0;
	for (int i = 0; i < word.length() - 2; i++) {
		if (word.at(i) == word.at(i + 2)) {
			repeatingLetter = true;
		}
	}
	if (repeatingLetter == true) {
		for (int j = 0; j < word.length() - 3; j++) {
			char currLetter = word.at(j);
			char nextLetter = word.at(j + 1);
			for (int k = j + 2; k < word.length() - 1; k++) {
				char secondCurrLetter = word.at(k);
				char secondNextLetter = word.at(k + 1);
				if ((currLetter == secondCurrLetter) && (nextLetter == secondNextLetter)) {
					return true;
				}
			}
		}
	}
	return false;
}

int main() {
	int niceCount = 0;

	ifstream myFile("data.txt");

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			lines.push_back(line);
		}
		myFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	for (int i = 0; i < lines.size(); i++) {
		if (naughtyOrNice2(lines[i]) == true) {
			niceCount++;
		}
	}

	cout << niceCount;

	cin.get();

}