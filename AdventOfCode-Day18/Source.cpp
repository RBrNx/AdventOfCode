#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
const int lightSize = 100;
int steps = 100;
int lightsOn;
bool lightArray[lightSize][lightSize];
bool lightArrayBuffer[lightSize][lightSize];
bool lightsBroke = true; //False for Part 1, True for Part 2

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

void swapBuffers() {
	for (int x = 0; x < lightSize; x++) {
		for (int y = 0; y < lightSize; y++) {
			lightArray[x][y] = lightArrayBuffer[x][y];
			lightArrayBuffer[x][y] = 0;
		}
	}
}

int calculateNeighbourhood(bool lightArray[lightSize][lightSize], int origX, int origY) {
	int onCount = 0;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			int offsetX = x - (3 / 2);
			int offsetY = y - (3 / 2);
		
			if (origX + offsetX >= 0 && origX + offsetX < lightSize && origY + offsetY >= 0 && origY + offsetY < lightSize) {
				if (lightArray[origX + offsetX][origY + offsetY] == 1) {
					if(offsetX != 0 || offsetY != 0) onCount++;
				}
			}
		}
	}

	return onCount;
}

void brokenLights(bool broken) {
	if (broken) {
		lightArray[0][0] = 1;
		lightArray[0][lightSize-1] = 1;
		lightArray[lightSize-1][0] = 1;
		lightArray[lightSize-1][lightSize-1] = 1;
	}
}

int main() {
	readFile("data.txt");

	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].length(); j++) {
			if (lines[i].at(j) == '#') {
				lightArray[i][j] = 1;
			}
			else if (lines[i].at(j) == '.') {
				lightArray[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < steps; i++) {
		for (int x = 0; x < lightSize; x++) {
			for (int y = 0; y < lightSize; y++) {
				brokenLights(lightsBroke);

				int neighboursOn = calculateNeighbourhood(lightArray, x, y);
				if (lightArray[x][y] == 1) {
					if (neighboursOn != 2 && neighboursOn != 3) {
						lightArrayBuffer[x][y] = 0;
					}
					else {
						lightArrayBuffer[x][y] = 1;
					}
				}
				else if (lightArray[x][y] == 0) {
					if (neighboursOn != 3) {
						lightArrayBuffer[x][y] = 0;
					}
					else {
						lightArrayBuffer[x][y] = 1;
					}
				}
			}
		}
		swapBuffers();
		brokenLights(lightsBroke);
	}

	for (int i = 0; i < lightSize; i++) {
		for (int j = 0; j < lightSize; j++) {
			if (lightArray[i][j] == 1) {
				lightsOn++;
			}
		}
	}
	
	cout << lightsOn;

	cin.get();
}