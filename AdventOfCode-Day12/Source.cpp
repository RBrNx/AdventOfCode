//PART 1 WORKS BUT 2 DOES NOT

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
vector<int> leftBArray;
vector<int> rightBArray;

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

void countNumbers(vector<string> lines) {
	int totalCount = 0;

	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].length(); j++) {
			size_t foundPos = lines[i].find_first_of("1234567890", j);
			size_t notFoundPos = lines[i].find_first_not_of("1234567890", foundPos);
			if (foundPos != string::npos && notFoundPos != string::npos) {
				if (lines[i].at(foundPos - 1) == '-') {
					totalCount += stoi(lines[i].substr(foundPos - 1, notFoundPos - 1), NULL, 10);
					//cout << lines[i].substr(foundPos - 1, notFoundPos-(foundPos-1));
					j = notFoundPos - 1;
				}
				else {
					totalCount += stoi(lines[i].substr(foundPos, notFoundPos - 1), NULL, 10);
					//cout << lines[i].substr(foundPos, notFoundPos-foundPos);
					j = notFoundPos - 1;
				}
			}
		}
	}

	cout << totalCount << endl;
}

vector<string> deleteRed(vector<string> lines) {
	string section;
	string subsection;

	/*for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].length(); j++) {
			int redPos = lines[i].find("red",j);
			int leftBPos = lines[i].rfind("{",redPos);
			int rightBPos = lines[i].find("}",redPos);
			section = lines[i].substr(leftBPos, (rightBPos - leftBPos)+1);
			int leftSBPos = section.find("[");
			int rightSBPos = section.find("]");
			if (leftSBPos >= 0 && rightSBPos >= 0) {
				subsection = section.substr(leftSBPos, (rightSBPos - leftSBPos) + 1);
				section.erase(leftSBPos, (rightSBPos - leftSBPos) + 1);
			}
			if (section.find("red") != string::npos){
				lines[i].erase(leftBPos+1, (rightBPos - leftBPos) -1);
				lines[i].insert(leftBPos+1, subsection);
				j = rightBPos;
			}
			else {
				j = rightBPos;
			}
			cout << lines[i].length() << endl;
		}

	}*/
	return lines;
}

int main() {
	readFile("data.txt");
	
	countNumbers(lines); //Part 1
	lines = deleteRed(lines); //Part 2
	countNumbers(lines); //Part 2


	std::cin.get();

}