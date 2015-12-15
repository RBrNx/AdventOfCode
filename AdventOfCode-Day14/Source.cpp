#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;
int furthestDistance = 0;
int mostPoints = 0;
string winningReindeer;

struct reindeer {
	string name;
	int speed;
	int defaultFlyTime;
	int defaultRestTime;
	int flightTime;
	int restingTime;
	int distanceTravelled;
	int points;
};

vector<struct reindeer> reindeers;

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

int main()
{
	int seconds = 2503;
	readFile("data.txt");

	for (int i = 0; i < lines.size(); i++)
	{
		string name = lines[i].substr(0, lines[i].find(' '));
		lines[i].erase(0, lines[i].find(' ') + 9);
		int speed = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);
		lines[i].erase(0, lines[i].find(' ') + 10);
		int flyTime = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);
		lines[i].erase(0, lines[i].find(' ') + 33);
		int restTime = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);

		reindeer Reindeer;
		Reindeer.name = name;
		Reindeer.speed = speed;
		Reindeer.flightTime = flyTime;
		Reindeer.restingTime = restTime;
		Reindeer.defaultFlyTime = flyTime;
		Reindeer.defaultRestTime = restTime;
		Reindeer.distanceTravelled = 0;
		Reindeer.points = 0;

		reindeers.push_back(Reindeer);
	}

	while (seconds > 0)
	{
		for (int i = 0; i < reindeers.size(); i++) {
			if (reindeers[i].flightTime > 0) {
				reindeers[i].flightTime--;
				reindeers[i].distanceTravelled += reindeers[i].speed;
			}
			else {
				if (reindeers[i].restingTime > 0) reindeers[i].restingTime--;
				else {
					reindeers[i].restingTime = reindeers[i].defaultRestTime;
					reindeers[i].flightTime = reindeers[i].defaultFlyTime;
					reindeers[i].flightTime--;
					reindeers[i].distanceTravelled += reindeers[i].speed;
				}
			}
		}
		for (int i = 0; i < reindeers.size(); i++) {
			if (reindeers[i].distanceTravelled > furthestDistance) {
				furthestDistance = reindeers[i].distanceTravelled;
			}
		}
		for (int i = 0; i < reindeers.size(); i++) {
			if (reindeers[i].distanceTravelled == furthestDistance) {
				reindeers[i].points++;
			}
		}
		seconds--;
	}

	furthestDistance = 0;
	for(int i = 0; i < reindeers.size(); i++) {
		if (reindeers[i].distanceTravelled > furthestDistance) {
			furthestDistance = reindeers[i].distanceTravelled;
			winningReindeer = reindeers[i].name;
		}
	}
	cout << winningReindeer << "- Furthest Distance: " << furthestDistance << endl;

	for (int i = 0; i < reindeers.size(); i++) {
		if (reindeers[i].points > mostPoints) {
			mostPoints = reindeers[i].points;
			winningReindeer = reindeers[i].name;
		}
	}
	cout << winningReindeer << "- Most Points: " << mostPoints << endl;

	
	cin.get();
}