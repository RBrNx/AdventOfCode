#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
vector<int> containers;
vector<int> combinations;
int litreCount;
int comboCount;
int minimumContainers = 100;

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

void go(int offset, int k) {
	if (k == 0) {
		litreCount = 0;
		for (int i = 0; i < combinations.size(); i++) {
			litreCount += combinations[i];
		}
		if (litreCount == 150) {
			if (combinations.size() < minimumContainers) { minimumContainers = combinations.size(); }
			comboCount++;
		}
		return;
	}
	for (int i = offset; i <= containers.size() - k; ++i) {
		combinations.push_back(containers[i]);
		go(i + 1, k - 1);
		combinations.pop_back();
	}
}


int main() {
	readFile("data.txt");

	for (int i = 0; i < lines.size(); i++) {
		containers.push_back(stoi(lines[i], NULL, 10));
	}

	for (int i = 2; i < containers.size(); i++) {
		go(0, i);
	}	
	cout << "There are " << comboCount << " different combinations that fit all 150 litres." << endl;
	comboCount = 0;

	go(0, minimumContainers);
	cout << "There are " << comboCount << " different combinations of " << minimumContainers << " containers that fit all 150 litres." << endl;

	cin.get();

}