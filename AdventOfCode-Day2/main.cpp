#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

struct present {
	int length;
	int width;
	int height;
};

int calculateSurfaceArea(int length, int width, int height) {
	int lw = 2 * length*width;
	int wh = 2 * width*height;
	int hl = 2 * height*length;
	int minimum = min({ length*width, width*height, height*length });
	
	return lw + wh + hl + minimum;
}

int calculateRibbon(int length, int width, int height) {
	int smallestPerimeter = min({ length * 2 + width * 2, width * 2 + height * 2, height * 2 + length * 2 }); //Ribbon to Wrap Present
	int cubicVolume = length * width * height; //Ribbon for Bow

	return smallestPerimeter + cubicVolume;
}

int main()
{
	vector<present> presents;
	vector<string> lines;
	string line;
	ifstream myFile ("data.txt");
	int totalWrappingPaper = 0;
	int totalRibbon = 0;
	
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
		height = lines[i];

		presents.resize(i+1);
		presents[i].length = std::stoi(length,NULL,10);
		presents[i].width = std::stoi(width, NULL, 10);
		presents[i].height = std::stoi(height, NULL, 10);
		
		totalWrappingPaper += calculateSurfaceArea(presents[i].length, presents[i].width, presents[i].height);
		totalRibbon += calculateRibbon(presents[i].length, presents[i].width, presents[i].height);
		//cout << presents[i].length << " " << presents[i].width << " " << presents[i].height << endl;
	}

	cout << totalWrappingPaper << endl;
	cout << totalRibbon << endl;

	cin.get();
	return 0;
}