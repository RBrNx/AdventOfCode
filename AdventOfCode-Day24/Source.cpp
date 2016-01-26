#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string line;
vector<string> instructions;
vector<int> packages;
vector<int> movedPackages;
vector<int> combinations;

vector<int> groupOne;
vector<int> groupTwo;
vector<int> groupThree;

int groupWeight = 0;
int weightCount;
vector<int> bestGroup = { 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 };

void readFile(string filename) {
	ifstream myFile(filename);

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			instructions.push_back(line);
		}
		myFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

void calculateGroupWeight(int groups) {
	for (int i = 0; i < packages.size(); i++) {
		groupWeight += packages[i];
	}

	groupWeight = groupWeight / groups;
}

void go(int offset, int k) {
	if (k == 0) {
		weightCount = 0;
		for (int i = 0; i < combinations.size(); i++) {
			weightCount += combinations[i];
			if (weightCount > groupWeight) {
				break;
			}
		}
		if (weightCount == groupWeight) {
			if (combinations.size() < bestGroup.size()) { bestGroup = combinations; }
			else if (combinations.size() == bestGroup.size()) {
				int QE1 = 0;
				for (int i = 0; i < combinations.size(); i++) {
					QE1 *= combinations[i];
				}
				int QE2 = 0;
				for (int i = 0; i < bestGroup.size(); i++) {
					QE2 *= bestGroup[i];
				}

				if (QE1 < QE2) {
					bestGroup = combinations;
				}
			}
		}
		return;
	}
	for (int i = offset; i <= packages.size() - k; ++i) {
		combinations.push_back(packages[i]);
		go(i + 1, k - 1);
		combinations.pop_back();
	}
}

int main() {
	readFile("data.txt");

	for (int i = 0; i < instructions.size(); i++) {
		packages.push_back(stoi(instructions[i]));
	}

	calculateGroupWeight(4); //3 for Part 1, 4 for Part 2
	for (int i = 2; i < packages.size(); i++) {
		go(0, i);
	}

	unsigned long long group1QE = 1;
	for (int i = 0; i < bestGroup.size(); i++) {
		group1QE *= bestGroup[i];
	}

	cout << "Group 1 Quantum Entanglement: " << group1QE << endl;
	cin.get();
}