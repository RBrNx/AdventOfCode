#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

struct auntSue {
	int children;
	int cats;
	int samoyeds;
	int pomeranians;
	int akitas;
	int vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
};

vector<struct auntSue> aunties;

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

auntSue addAuntSue(auntSue AuntSue, string compound, int compoundValue) {
	if (compound == "children") {
		AuntSue.children = compoundValue;
	}
	if (compound == "cats") {
		AuntSue.cats = compoundValue;
	}
	if (compound == "samoyeds") {
		AuntSue.samoyeds = compoundValue;
	}
	if (compound == "pomeranians") {
		AuntSue.pomeranians = compoundValue;
	}
	if (compound == "akitas") {
		AuntSue.akitas = compoundValue;
	}
	if (compound == "vizslas") {
		AuntSue.vizslas = compoundValue;
	}
	if (compound == "goldfish") {
		AuntSue.goldfish = compoundValue;
	}
	if (compound == "trees") {
		AuntSue.trees = compoundValue;
	}
	if (compound == "cars") {
		AuntSue.cars = compoundValue;
	}
	if (compound == "perfumes") {
		AuntSue.perfumes = compoundValue;
	}

	return AuntSue;
}


int main() {
	readFile("data.txt");

	for (int i = 0; i < lines.size(); i++)
	{
		lines[i].erase(0, lines[i].find(':')+2); //Erase "Sue #: "
		string compound1 = lines[i].substr(0, lines[i].find(':'));
		lines[i].erase(0, compound1.length()+2); //Erases Compound 1 + ": "
		int compound1Value = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 2); //Erases Compound 1 value and ", "
		
		string compound2 = lines[i].substr(0, lines[i].find(':'));
		lines[i].erase(0, compound2.length() + 2); //Erases Compound 2 + ": "
		int compound2Value = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 2); //Erases Compound 2 value and ", "

		string compound3 = lines[i].substr(0, lines[i].find(':'));
		lines[i].erase(0, compound3.length() + 2); //Erases Compound 3 + ": "
		int compound3Value = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 2); //Erases Compound 3 value and ", "

		struct auntSue AuntSue = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		
		AuntSue = addAuntSue(AuntSue, compound1, compound1Value);
		AuntSue = addAuntSue(AuntSue, compound2, compound2Value);
		AuntSue = addAuntSue(AuntSue, compound3, compound3Value);
		aunties.push_back(AuntSue);		
	}

	struct auntSue AuntSueTest = { 3, 7, 2, 3, 0, 0, 5, 3 ,2, 1 };
	for (int i = 0; i < aunties.size(); i++) {
		int matchCounter = 0;
		
		if (aunties[i].children == AuntSueTest.children && aunties[i].children > 0) {
			matchCounter++;
		}
		if (aunties[i].cats >= AuntSueTest.cats && aunties[i].cats > 0) { // == instead of >= for Part 1
			matchCounter++;
		}
		if (aunties[i].samoyeds == AuntSueTest.samoyeds && aunties[i].samoyeds > 0) {
			matchCounter++;
		}
		if (aunties[i].pomeranians <= AuntSueTest.pomeranians && aunties[i].pomeranians > 0) { // == instead of <= for Part 1
			matchCounter++;
		}
		if (aunties[i].akitas == AuntSueTest.akitas && aunties[i].akitas > 0) {
			matchCounter++;
		}
		if (aunties[i].vizslas == AuntSueTest.vizslas && aunties[i].vizslas > 0) {
			matchCounter++;
		}
		if (aunties[i].goldfish <= AuntSueTest.goldfish && aunties[i].goldfish > 0) { // == instead of <= for Part 1
			matchCounter++;
		}
		if (aunties[i].trees >= AuntSueTest.trees && aunties[i].trees > 0) { // == instead of >= for Part 1
			matchCounter++;
		}
		if (aunties[i].cars == AuntSueTest.cars && aunties[i].cars > 0) {
			matchCounter++;
		}
		if (aunties[i].perfumes == AuntSueTest.perfumes && aunties[i].perfumes > 0) {
			matchCounter++;
		}

		if (matchCounter == 3) {
			cout << "Aunt Sue: " << i+1 << endl;
		}
	}
	cin.get();
}