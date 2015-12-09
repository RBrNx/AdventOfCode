#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

int codeCount(string line) {
	int count = 0;
	int slashPosition;
	if ((slashPosition = line.find('\\')) > 0) {
		if ((line.substr(slashPosition+1, 1)) == "\\"){ // == "\"
			line.erase(slashPosition, 2); //Delete the 2 backslashes
			count += 1;
		}
		else if ((line.substr(slashPosition + 1, 1)) == "\"") { // == " " "
			line.erase(slashPosition, 2); //Delete the backslash and quote
			count += 1;
		}
	}
	count += line.length();

	return count;
}

int memoryCount(string line) {

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

	cout << codeCount(lines[2]);

	cin.get();
}