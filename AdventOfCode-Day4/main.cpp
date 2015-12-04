#include "md5.h"
#include<iostream>>
#include<string>
#include<sstream>

using namespace std;

int main()
{
	string input = "iwrupvqb";
	string md5Output;
	ostringstream oss;

	int number = 0;
	bool found = false;

	while (!found)
	{
		oss << number;
		input += oss.str();

		md5Output = md5(input);

		if (md5Output.substr(0,5) == "00000")
		{
			found = true;
			cout << number << endl;
		}
		else {
			found = false;
			number++;
		}
	}

	cin.get();
	return 0;	
}