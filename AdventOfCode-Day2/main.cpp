#include<iostream>
#include<string>
#include<fstream>
#include <vector>

using namespace std;


int main()
{
	vector<string> lines;
	string line;
	ifstream myFile ("input.txt");
	
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

	string length, width, height;
	
	for (int i = 0; i < lines.size(); i++)
	{
		length = lines[i].substr(0, lines[i].find('x'));
		lines[i].erase(0, (length.length() + 1));
		width = lines[i].substr(0, lines[i].find('x'));
		lines[i].erase(0, width.length() + 1);
		height = lines[i].substr(0, lines[i].length());
		

		cout << length << " " << width << " " << endl;
	}
	cin.get();
	return 0;
}

int calcLW(int length, int width)
{
	return (2 * length*width);
}

int calcWH(int width, int height)
{
	return (2 * width*height);
}

int calcHL(int height, int length)
{
	return (2 * height*length);
}