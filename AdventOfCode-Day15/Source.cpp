#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lines;
string line;

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

struct bestCookie {
	int spoonfulsIngredient1;
	int spoonfulsIngredient2;
	int spoonfulsIngredient3;
	int spoonfulsIngredient4;
	int calorieCount;
	int highestScore = 0;
} BestCookie;

struct ingredient {
	string name;
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;
	int spoonfuls;
};

vector<struct ingredient> ingredients;

int CapacityScore;
int DurabilityScore;
int FlavourScore;
int TextureScore;
int CalorieCount;

void partOne() {
	for (int a = 0; a <= 100; a++) {
		for (int b = 0; b <= 100 - a; b++) {
			for (int c = 0; c <= 100 - a - b; c++) {
				ingredients[0].spoonfuls = a, ingredients[1].spoonfuls = b, ingredients[2].spoonfuls = c, ingredients[3].spoonfuls = 100 - a - b - c;
				if (a > 0 && b > 0 && c > 0) {
					int m = 3;
				}

				if ((CapacityScore = ((ingredients[0].spoonfuls * ingredients[0].capacity) + (ingredients[1].spoonfuls * ingredients[1].capacity) + (ingredients[2].spoonfuls * ingredients[2].capacity) + (ingredients[3].spoonfuls * ingredients[3].capacity))) < 0) { CapacityScore = 0; }
				if ((DurabilityScore = ((ingredients[0].spoonfuls * ingredients[0].durability) + (ingredients[1].spoonfuls * ingredients[1].durability) + (ingredients[2].spoonfuls * ingredients[2].durability) + (ingredients[3].spoonfuls * ingredients[3].durability))) < 0) { DurabilityScore = 0; }
				if ((FlavourScore = ((ingredients[0].spoonfuls * ingredients[0].flavour) + (ingredients[1].spoonfuls * ingredients[1].flavour) + (ingredients[2].spoonfuls * ingredients[2].flavour) + (ingredients[3].spoonfuls * ingredients[3].flavour))) < 0) { FlavourScore = 0; }
				if ((TextureScore = ((ingredients[0].spoonfuls * ingredients[0].texture) + (ingredients[1].spoonfuls * ingredients[1].texture) + (ingredients[2].spoonfuls * ingredients[2].texture) + (ingredients[3].spoonfuls * ingredients[3].texture))) < 0) { TextureScore = 0; }

				int totalScore = CapacityScore * DurabilityScore * FlavourScore * TextureScore;

				if (totalScore > BestCookie.highestScore) {
					BestCookie.highestScore = totalScore;
					BestCookie.spoonfulsIngredient1 = ingredients[0].spoonfuls;
					BestCookie.spoonfulsIngredient2 = ingredients[1].spoonfuls;
					BestCookie.spoonfulsIngredient3 = ingredients[2].spoonfuls;
					BestCookie.spoonfulsIngredient4 = ingredients[3].spoonfuls;
				}
			}
		}
	}

	std::cout << "Score: " << BestCookie.highestScore << endl;;
	std::cout << BestCookie.spoonfulsIngredient1 << " Spoonfuls of Frosting, " << BestCookie.spoonfulsIngredient2 << " Spoonfuls of Candy, " << BestCookie.spoonfulsIngredient3 << " Spoonfuls of Butterscotch, " << BestCookie.spoonfulsIngredient4 << " Spoonfuls of Sugar" << endl;
}

void partTwo() {
	for (int a = 0; a <= 100; a++) {
		for (int b = 0; b <= 100 - a; b++) {
			for (int c = 0; c <= 100 - a - b; c++) {
				ingredients[0].spoonfuls = a, ingredients[1].spoonfuls = b, ingredients[2].spoonfuls = c, ingredients[3].spoonfuls = 100 - a - b - c;
				if (a > 0 && b > 0 && c > 0) {
					int m = 3;
				}

				if ((CapacityScore = ((ingredients[0].spoonfuls * ingredients[0].capacity) + (ingredients[1].spoonfuls * ingredients[1].capacity) + (ingredients[2].spoonfuls * ingredients[2].capacity) + (ingredients[3].spoonfuls * ingredients[3].capacity))) < 0) { CapacityScore = 0; }
				if ((DurabilityScore = ((ingredients[0].spoonfuls * ingredients[0].durability) + (ingredients[1].spoonfuls * ingredients[1].durability) + (ingredients[2].spoonfuls * ingredients[2].durability) + (ingredients[3].spoonfuls * ingredients[3].durability))) < 0) { DurabilityScore = 0; }
				if ((FlavourScore = ((ingredients[0].spoonfuls * ingredients[0].flavour) + (ingredients[1].spoonfuls * ingredients[1].flavour) + (ingredients[2].spoonfuls * ingredients[2].flavour) + (ingredients[3].spoonfuls * ingredients[3].flavour))) < 0) { FlavourScore = 0; }
				if ((TextureScore = ((ingredients[0].spoonfuls * ingredients[0].texture) + (ingredients[1].spoonfuls * ingredients[1].texture) + (ingredients[2].spoonfuls * ingredients[2].texture) + (ingredients[3].spoonfuls * ingredients[3].texture))) < 0) { TextureScore = 0; }
				CalorieCount = ((ingredients[0].spoonfuls * ingredients[0].calories) + (ingredients[1].spoonfuls * ingredients[1].calories) + (ingredients[2].spoonfuls * ingredients[2].calories) + (ingredients[3].spoonfuls * ingredients[3].calories));

				int totalScore = CapacityScore * DurabilityScore * FlavourScore * TextureScore;

				if (totalScore > BestCookie.highestScore && CalorieCount == 500) {
					BestCookie.highestScore = totalScore;
					BestCookie.spoonfulsIngredient1 = ingredients[0].spoonfuls;
					BestCookie.spoonfulsIngredient2 = ingredients[1].spoonfuls;
					BestCookie.spoonfulsIngredient3 = ingredients[2].spoonfuls;
					BestCookie.spoonfulsIngredient4 = ingredients[3].spoonfuls;
					BestCookie.calorieCount = CalorieCount;
				}
			}
		}
	}

	std::cout << endl << endl;
	std::cout << "Score: " << BestCookie.highestScore << endl;;
	std::cout << BestCookie.spoonfulsIngredient1 << " Spoonfuls of Frosting, " << BestCookie.spoonfulsIngredient2 << " Spoonfuls of Candy, " << BestCookie.spoonfulsIngredient3 << " Spoonfuls of Butterscotch, " << BestCookie.spoonfulsIngredient4 << " Spoonfuls of Sugar, " << BestCookie.calorieCount << " Calories." << endl;
}

void resetBestCookie() {
	BestCookie.calorieCount = 0;
	BestCookie.highestScore = 0;
	BestCookie.spoonfulsIngredient1 = 0;
	BestCookie.spoonfulsIngredient2 = 0;
	BestCookie.spoonfulsIngredient3 = 0;
	BestCookie.spoonfulsIngredient4 = 0;
}

int main() {
	readFile("data.txt");
	for (int i = 0; i < lines.size(); i++) {
		string Name = lines[i].substr(0, lines[i].find(':'));
		lines[i].erase(0, Name.length() + 11); //Erases Name + ": " + Capacity

		int Capacity = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 13); //Erases Capacity value and "Durability "

		int Durability = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 9); //Erases Durability value and "Flavour "

		int Flavour = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 10); //Erases Flavour value and "Texture "

		int Texture = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 11); //Erases Texture value and "Calories "

		int Calories = stoi(lines[i].substr(0, lines[i].find(',')), NULL, 10);
		lines[i].erase(0, lines[i].find(',') + 2); //Erases Calories value

		struct ingredient Ingredient;

		Ingredient.name = Name;
		Ingredient.capacity = Capacity;
		Ingredient.durability = Durability;
		Ingredient.flavour = Flavour;
		Ingredient.texture = Texture;
		Ingredient.calories = Calories;

		ingredients.push_back(Ingredient);
	}

	partOne();
	resetBestCookie();
	partTwo();


	std::cin.get();
}