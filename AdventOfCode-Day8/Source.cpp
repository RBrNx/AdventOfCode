#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

int Count(vector<string> lines) {
	int totalCodeChar = 0;
	int totalMemChar = 0;
	
	for (int i = 0; i < lines.size(); i++) {
		int j = 0;

		while(j < lines[i].length()) {
			if (lines[i].at(j) == '\\') {
				j++;
				if (lines[i].at(j) == 'x') {
					j += 3;
					totalCodeChar += 4;
					totalMemChar += 1;
				}
				else {
					j++;
					totalCodeChar += 2;
					totalMemChar += 1;
				}
			}
			else if (lines[i].at(j) == '\"') {
				j++;
				totalCodeChar += 1;
			}
			else {
				j++;
				totalCodeChar += 1;
				totalMemChar += 1;
			}
		}
	}

	int difference = totalCodeChar - totalMemChar;
	return difference;
}

int CountPart2(vector<string> lines) {
	int totalCodeChar = 0;
	int totalMemChar = 0;

	for (int i = 0; i < lines.size(); i++) {
		int j = 0;
		totalMemChar += 2;

		while (j < lines[i].length()) {
			if (lines[i].at(j) == '\\') {
				j++;
				totalMemChar += 2;
				if (lines[i].at(j) == 'x') {
					j += 3;
					totalCodeChar += 4;
					totalMemChar += 3;
				}
				else {
					j++;
					totalCodeChar += 2;
					totalMemChar += 2;
				}
			}
			else if (lines[i].at(j) == '\"') {
				j++;
				totalCodeChar += 1;
				totalMemChar += 2;
			}
			else {
				j++;
				totalCodeChar += 1;
				totalMemChar += 1;
			}
		}
	}

	int difference = totalMemChar - totalCodeChar;
	return difference;
}


void readFile(string filename) {
	ifstream myFile(filename);

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
}

int main() {
	readFile("data.txt");

	cout << CountPart2(lines);
	cin.get();
}