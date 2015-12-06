#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
bool lightArray[1000][1000];

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

void toggleLights(int leftX, int leftY, int rightX, int rightY) {
	for (int y = leftY; y <= rightY; y++) {
		for (int x = leftX; x <= rightX; x++) {
			lightArray[y][x] = !lightArray[y][x];
		}
	}
}

void onOffLights(int onOff, int leftX, int leftY, int rightX, int rightY) {
	for (int y = leftY; y <= rightY; y++) {
		for (int x = leftX; x <= rightX; x++) {
			lightArray[y][x] = onOff;
		}
	}
}

int main() {
	int onOff = 0;
	int lightsOn = 0;

	readFile("data.txt");
	
	for (int i = 0; i < lines.size(); i++) {
		string instruction = lines[i].substr(0, lines[i].find(' ')); //finds first instruction
		lines[i].erase(0, (instruction.length() + 1));

		if (instruction == "turn") {
			string OnOrOff = lines[i].substr(0, lines[i].find(' ')); //finds 'on' or 'off' if necessary
			lines[i].erase(0, (OnOrOff.length() + 1));
			if (OnOrOff == "on") {
				onOff = 1;
			}
			else {
				onOff = 0;
			}
		}
		
		string leftCornerCoord = lines[i].substr(0, lines[i].find(' ')); //finds top left coord
		lines[i].erase(0, (leftCornerCoord.length() + 9)); //deletes left-coord and "through" from loaded string
		int LeftX = std::stoi(leftCornerCoord.substr(0, leftCornerCoord.find(',')));
		leftCornerCoord.erase(0, leftCornerCoord.find(',')+1);
		int LeftY = std::stoi(leftCornerCoord);

		string rightCornerCoord = lines[i]; //rest of string is bottom right corner
		int RightX = std::stoi(rightCornerCoord.substr(0, rightCornerCoord.find(',')));
		rightCornerCoord.erase(0, rightCornerCoord.find(',') + 1);
		int RightY = std::stoi(rightCornerCoord);

		if (instruction == "turn") {
			onOffLights(onOff, LeftX, LeftY, RightX, RightY);
		}
		else if (instruction == "toggle") {
			toggleLights(LeftX, LeftY, RightX, RightY);
		}
	}

	//onOffLights(1, 0, 0, 999, 999);

	for (int y = 0; y < 1000; y++) {
		for (int x = 0; x < 1000; x++) {
			if (lightArray[y][x] == 1) {
				lightsOn++;
			}
		}
	}

	cout << lightsOn;
	cin.get();
}