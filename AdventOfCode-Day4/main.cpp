#include "md5.h"
#include<iostream>>
#include<string>

using namespace std;

int main()
{
	string input = "iwrupvqb";
	string md5Output;

	int number = 0;
	bool found = false;

	while (!found)
	{
		input = "iwrupvqb";
		input += to_string(number);
			
		md5Output = md5(input);

		cout << md5Output << "   " << number << endl;

		if (md5Output.substr(0,6) == "000000")
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