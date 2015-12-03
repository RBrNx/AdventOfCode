#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<string> lines;
	string line;
	vector<char> santaMoves(1);
	int leftRightCount = 0;
	int upDownCount = 0;
	ifstream myFile("data.txt");
	vector<vector<int>> Grid(1000, vector<int>(1000, 0));

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

	for (int i = 0; i < lines[0].length(); i++)
	{
		if (lines[0].at(i) == '^' || lines[0].at(i) == 'v') {
			upDownCount++;
		}
		else if (lines[0].at(i) == '<' || lines[0].at(i) == '>') {
			leftRightCount++;
		}

		if (i == santaMoves.size()) {
			santaMoves.resize(i + 1);
		}
		santaMoves[i] = lines[0].at(i);
	}
	
	int x = 999;
	int y = 999;
	int robox = 999;
	int roboy = 999;

	Grid[y][x] = 1;
	for (int i = 0; i < santaMoves.size(); i+=2) {

		// Move Santa 1 Square
		if (santaMoves[i] == '<'){
			x = x - 1;
			Grid[y][x]++;
		}
		else if (santaMoves[i] == '>') {
			x = x + 1;
			if (x == Grid[0].size()) {
				for (int i = 0; i < Grid.size(); i++) {
					Grid[i].resize(Grid[i].size() + 1);
				}
			}
			Grid[y][x]++;
		}
		else if (santaMoves[i] == '^') {
			y = y + 1;
			if (y == Grid.size()) {
				Grid.push_back(vector<int>(Grid[0].size(), 0));
			}
			Grid[y][x]++;
		}
		else if (santaMoves[i] == 'v') {
			y = y - 1;
			Grid[y][x]++;
		}

		// Move RoboSanta 1 Square
		if (santaMoves[i+1] == '<') {
			robox = robox - 1;
			Grid[roboy][robox]++;
		}
		else if (santaMoves[i+1] == '>') {
			robox = robox + 1;
			if (robox == Grid[0].size()) {
				for (int i = 0; i < Grid.size(); i++) {
					Grid[i].resize(Grid[i].size() + 1);
				}
			}
			Grid[roboy][robox]++;
		}
		else if (santaMoves[i+1] == '^') {
			roboy = roboy + 1;
			if (roboy == Grid.size()) {
				Grid.push_back(vector<int>(Grid[0].size(), 0));
			}
			Grid[roboy][robox]++;
		}
		else if (santaMoves[i+1] == 'v') {
			roboy = roboy - 1;
			Grid[roboy][robox]++;
		}
	}

	int houseCount = 0;
	for (int y = 0; y < Grid.size(); y++) {
		for (int x = 0; x < Grid[0].size(); x++) {
			if (Grid[y][x] > 0) {
				houseCount++;
			}
		}
	}

	cout << houseCount << endl;
	cin.get();
}