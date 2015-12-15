#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
const int numberofPeople = 9; //Part 1 - 8, Part 2 - 9
int happinessArray[numberofPeople][numberofPeople];
vector<string> people;
int totalHappiness = 0;
int smallestCombo = 100000;
int biggestCombo = 0;

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
		totalHappiness = 0;
		for (int FromIter = 0, ToIter = 1; FromIter < n - 1; FromIter++, ToIter++) {
			totalHappiness += happinessArray[combo[FromIter]][combo[ToIter]];
			totalHappiness += happinessArray[combo[ToIter]][combo[FromIter]];
			if (ToIter == numberofPeople-1) {
				totalHappiness += happinessArray[combo[numberofPeople-1]][combo[0]];
				totalHappiness += happinessArray[combo[0]][combo[numberofPeople-1]];
			}
		}
		if (totalHappiness > biggestCombo) {
			biggestCombo = totalHappiness;
		}
		if (totalHappiness < smallestCombo) {
			smallestCombo = totalHappiness;
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
	readFile("data2.txt"); //Data.txt Part 1, Data2.txt Part 2
	int intPersonOne = 0;
	int intPersonTwo = 0;
	bool foundPerson = false;

	for (int i = 0; i < lines.size(); i++) {
		string Name = lines[i].substr(0, lines[i].find(' ')); //finds first name
		lines[i].erase(0, (Name.length() + 7)); //erases spaces + "would"
		string Operation = lines[i].substr(0, lines[i].find(' '));
		if (Operation == "lose") { lines[i].insert(lines[i].find(' ')+1, 1, '-'); }
		lines[i].erase(0, (Operation.length() + 1)); //erases operation + space;
		int Happiness = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);
		lines[i].erase(0, lines[i].find(' ') + 36);
		string otherName = lines[i].substr(0, lines[i].find('.'));

		for (int j = 0; j < people.size(); j++) {
			if (Name == people[j]) {
				intPersonOne = j;
				foundPerson = true;
			}
		}
		if (!foundPerson) {
			people.push_back(Name);
			intPersonOne = people.size() - 1;
		}

		foundPerson = false;
		for (int j = 0; j < people.size(); j++) {
			if (otherName == people[j]) {
				intPersonTwo = j;
				foundPerson = true;
			}
		}
		if (!foundPerson) {
			people.push_back(otherName);
			intPersonTwo = people.size() - 1;
		}

		happinessArray[intPersonOne][intPersonTwo] = Happiness;
	}

	int ints[numberofPeople];

	for (int i = 0; i < numberofPeople; i++) {
		ints[i] = i;
	}

	//calculate permutation
	perm(ints, numberofPeople, 0);
	cout << biggestCombo << endl;
	
	cin.get();
}