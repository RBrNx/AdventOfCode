#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
int distanceArray[8][8];
vector<string> places;
vector<string> combinations;
int totalComboDistance = 0;
int smallestCombo = 10000000000;

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

void swap(int places[], int i, int j) {
	int temp = 0;
	temp = places[i];
	places[i] = places[j];
	places[j] = temp;
}

void perm(int combo[], int n, int i) {
	if (i == n) {
		totalComboDistance = 0;
		for (int FromIter = 0, ToIter = 1; FromIter < n-1; FromIter++, ToIter++) {
			totalComboDistance += distanceArray[combo[FromIter]][combo[ToIter]];
		}
		if (totalComboDistance < smallestCombo) {
			smallestCombo = totalComboDistance;
		}
	}
	else {
		for (int j = i; j < n; j++) {
			swap(combo, i, j);
			perm(combo, n, i + 1);
			swap(combo, i, j);
		}
	}

}

int main() {
	readFile("data.txt");
	int intFrom = 0;
	int intTo = 0;
	bool foundPlace = false;
	string result[8];

	for (int i = 0; i < lines.size(); i++) {
		string From = lines[i].substr(0, lines[i].find(' ')); //finds first location
		lines[i].erase(0, (From.length() + 4)); //erases spaces + "to"
		string To = lines[i].substr(0, lines[i].find(' '));
		lines[i].erase(0, (To.length() + 3)); //erases spaces + "=";
		int Distance = stoi(lines[i], NULL, 10);

		for (int j = 0; j < places.size(); j++) {
			if (From == places[j]) {
				intFrom = j;
				foundPlace = true;
			}
		}
		if (!foundPlace) {
			places.push_back(From);
			intFrom = places.size()-1;
		}

		foundPlace = false;
		for (int j = 0; j < places.size(); j++) {
			if (To == places[j]) {
				intTo = j;
				foundPlace = true;
			}
		}
		if (!foundPlace) {
			places.push_back(To);
			intTo = places.size()-1;
		}

		distanceArray[intFrom][intTo] = Distance;
		distanceArray[intTo][intFrom] = Distance;
	}

	int ints[8];

	for (int i = 0; i < 8; i++) {
		ints[i] = i;
	}

	//calculate permutation
	perm(ints, 8, 0);
	//take combo 1
	//from starts on combo[0] 
	// to starts on combo[1]
	// loop til from = end-1
	//count+= distanceArray[fromIterator][toIterator];
	//have int min start as count? or stupidly high number? if next count < min then min = next count
	cout << smallestCombo;

	cin.get();
}