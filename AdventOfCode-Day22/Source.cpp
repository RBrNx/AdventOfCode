#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct player {
	int HP;
	int Mana;
	int Armor;
	int manaSpent;
};

struct boss {
	int HP;
	int Damage;
};

struct player Player;
struct boss Boss;
int lowestManaCount = 3000;

class Spell {
private:
	string Name;
	int ManaCost;
	int TurnLength;
	int timer;
	bool active;
	int EffectValue;
	bool Debug;

public:
	Spell::Spell(string name, int manaCost, int turnLength, int effectValue, bool debug) {
		Name = name;
		ManaCost = manaCost;
		TurnLength = turnLength;
		timer = turnLength;
		active = false;
		EffectValue = effectValue;
		Debug = debug;

	}

	void Spell::CastSpell(bool alreadyActive) {
		if (active) {
			if (Name == "Magic Missile") CastMagicMissile();
			if (Name == "Drain") CastDrain();
			if (Name == "Shield") CastShield(alreadyActive);
			if (Name == "Poison") CastPoison(alreadyActive);
			if (Name == "Recharge") CastRecharge(alreadyActive);
			timer--;
			if (Debug == true && (Name == "Shield" || Name == "Poison" || Name == "Recharge")) cout << Name << " Timer: " << timer << endl;
			if (timer == 0) {
				timer = TurnLength;
				active = false;
				if (Name == "Shield") Player.Armor = 0;
			}
		}
		else {
			if (Player.Mana > ManaCost) {
				active = true;
				if (Debug) cout << "Player casts " << Name << endl;
				CastSpell(false);
			}
		}
	}

	bool Spell::isActive() {
		return active;
	}

	void Spell::CastMagicMissile() {
		if (Debug) cout << "Magic Missile Deals " << EffectValue << " Damage" << endl;
		Player.Mana -= ManaCost;
		Player.manaSpent += ManaCost;
		Boss.HP -= EffectValue;
	}

	void Spell::CastDrain() {
		if (Debug) cout << "Drain Deals " << EffectValue << " Damage and Recovers " << EffectValue << " Health" << endl;
		Player.Mana -= ManaCost;
		Player.manaSpent += ManaCost;
		Boss.HP -= EffectValue;
		Player.HP += EffectValue;
	}

	void Spell::CastShield(bool alreadyActive) {
		//if (Debug) cout << "Shield is Active" << endl;
		if (!alreadyActive) {
			Player.Mana -= ManaCost;
			Player.manaSpent += ManaCost;
		}
		Player.Armor = 7;
	}

	void Spell::CastPoison(bool alreadyActive) {
		if (!alreadyActive) {
			Player.Mana -= ManaCost;
			Player.manaSpent += ManaCost;
		}
		if (alreadyActive) {
			Boss.HP -= EffectValue;
			if (Debug) cout << "Poison Deals " << EffectValue << " Damage" << endl;
		}
	}

	void Spell::CastRecharge(bool alreadyActive) {
		if (!alreadyActive) {
			if (Debug) cout << EffectValue << " Mana is regained" << endl;
			Player.Mana -= ManaCost;
			Player.manaSpent += ManaCost;
		}
		if (alreadyActive) {
			Player.Mana += EffectValue;
		}
	}

	int Spell::returnManaCost() {
		return ManaCost;
	}

	string Spell::returnName() {
		return Name;
	}
};

vector<Spell> playerSpells;
vector<string> castSpells;
vector<string> bestSpells;

void getSpell() {
	vector<int> nonActiveSpells;
	bool spellChosen = false;
	int tries = 0;

	for (int i = 0; i < playerSpells.size(); i++) {
		if (!playerSpells[i].isActive()) {
			nonActiveSpells.push_back(i);
		}
	}

	while (!spellChosen && tries < nonActiveSpells.size()) {
		int random = rand() % nonActiveSpells.size();
		int chosenSpell = nonActiveSpells[random];
		if (playerSpells[chosenSpell].returnManaCost() < Player.Mana) {
			if (Player.manaSpent < lowestManaCount) {
				playerSpells[chosenSpell].CastSpell(false);
				spellChosen = true;
				castSpells.push_back(playerSpells[chosenSpell].returnName());
			}
		}
		tries++;
	}
}

void playersTurn(bool debug, bool hardMode) {
	if (debug) {
		cout << endl;
		cout << "-- Player Turn --" << endl;
		cout << "Player has " << Player.HP << " HP, " << Player.Armor << " Armor, " << Player.Mana << " Mana." << endl;
		cout << "Boss has " << Boss.HP << " HP." << endl;
	}

	if (hardMode) {
		Player.HP -= 1;
		if (debug) cout << "Player loses 1 HP due to HardMode" << endl;
	}

	if (Player.HP > 0) {
		for (int i = 0; i < playerSpells.size(); i++) {
			if (playerSpells[i].isActive()) {
				playerSpells[i].CastSpell(true);
			}
		}
	}

	getSpell();
}

void bossTurn(bool debug) {
	if (debug) {
		cout << endl;
		cout << "-- Boss Turn --" << endl;
		cout << "Player has " << Player.HP << " HP, " << Player.Armor << " Armor, " << Player.Mana << " Mana." << endl;
		cout << "Boss has " << Boss.HP << " HP." << endl;
	}

	for (int i = 0; i < playerSpells.size(); i++) {
		if (playerSpells[i].isActive()) {
			playerSpells[i].CastSpell(true);
		}
	}

	if (Boss.HP > 0) {
		int BossDamage = (Boss.Damage - Player.Armor) > 0 ? Boss.Damage - Player.Armor : -1;
		Player.HP = Player.HP - BossDamage;
		if (debug) cout << "Boss Deals " << BossDamage << " Damage." << endl;
	}
}

void reset(bool debug) {
	Player.HP = 50, Player.Mana = 500, Player.Armor = 0, Player.manaSpent = 0;
	Boss.HP = 55, Boss.Damage = 8;
	//Player.HP = 10, Player.Mana = 250, Player.Armor = 0, Player.manaSpent = 0;
	//Boss.HP = 13, Boss.Damage = 8;
	playerSpells.clear();
	playerSpells.push_back(Spell("Magic Missile", 53, 1, 4, debug));
	playerSpells.push_back(Spell("Drain", 73, 1, 2, debug));
	playerSpells.push_back(Spell("Shield", 113, 7, 7, debug)); //Shield is 7 instead of 6 turns here, due to the way this is coded, it works out at 6 turns though
	playerSpells.push_back(Spell("Poison", 173, 7, 3, debug)); //Poison is 7 instead of 6 turns here, due to the way this is coded, it works out at 6 turns though
	playerSpells.push_back(Spell("Recharge", 229, 6, 101, debug)); //Recharge is 6 instead of 5 turns here, due to the way this is coded, it works out at 5 turns though
}

int main() {
	bool debug = false;
	bool hardMode = false;

	reset(debug);
	srand(time(NULL));

	for (int i = 0; i < 10000; i++) {
		reset(debug);
		while (Player.HP > 0 && Boss.HP > 0) {
			if (Player.Mana < 53) break;
			playersTurn(debug, hardMode);
			if (Player.HP <= 0) break;
			bossTurn(debug);
		}

		if (Boss.HP <= 0 && Player.HP > 0) {
			if (Player.manaSpent < lowestManaCount) {
				lowestManaCount = Player.manaSpent;
				bestSpells.clear();
				for (int i = 0; i < castSpells.size(); i++) {
					bestSpells.push_back(castSpells[i]);
				}
			}
			else {
				castSpells.clear();
			}
		}
		else {
			castSpells.clear();
		}
	}

	for (int i = 0; i < bestSpells.size(); i++) {
		cout << bestSpells[i] << endl;
	}
	cout << lowestManaCount;
	//cout << "Finshed" << endl;
	cin.get();
}