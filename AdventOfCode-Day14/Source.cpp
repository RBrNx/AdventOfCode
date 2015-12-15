#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

struct reindeer {
	string name;
	int speed;
	int flyTime;
	int restTime;
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
		lines[i].erase(0, lines[i].find(' ') + 8);
		int speed = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);
		lines[i].erase(0, lines[i].find(' ') + 9);
		int flyTime = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);
		lines[i].erase(0, lines[i].find(' ') + 32);
		int restTime = stoi(lines[i].substr(0, lines[i].find(' ')), NULL, 10);

		reindeer Reindeer;
		Reindeer.name = name;
		Reindeer.speed = speed;
		Reindeer.flyTime = flyTime;
		Reindeer.restTime = restTime;

		reindeers.push_back(Reindeer);
	}

	while (seconds > 0)
	{




		seconds--;
	}
}