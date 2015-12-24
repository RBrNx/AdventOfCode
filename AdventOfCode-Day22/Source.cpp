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
				if (Debug && Name == "Shield" || Name == "Poison" || Name == "Recharge") cout << Name << " Timer: " << timer << endl;
				if (timer == 0) {
					timer = TurnLength;
					active = false;
					if (Name == "Shield") Player.Armor = 0;
				}
			}
			else {
				if (Player.Mana > ManaCost) {
					active = true;
					cout << "Player casts " << Name << endl;
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
				if (Debug) cout << "Poison Deals " << EffectValue << " Damage" << endl;
				Player.Mana -= ManaCost;
				Player.manaSpent += ManaCost;
			}
			Boss.HP -= EffectValue;
		}

		void Spell::CastRecharge(bool alreadyActive) {
			if (!alreadyActive) {
				if (Debug) cout << EffectValue << " Mana is regained" << endl;
				Player.Mana -= ManaCost;
				Player.manaSpent += ManaCost;
			}
			Player.Mana += EffectValue;
		}

		int Spell::returnManaCost() {
			return ManaCost;
		}	
};

vector<Spell> playerSpells;

void getSpell() {
	vector<int> nonActiveSpells;

	for (int i = 0; i < playerSpells.size(); i++) {
		if (!playerSpells[i].isActive()) {
			nonActiveSpells.push_back(i);
		}
	}

	int random = rand() % nonActiveSpells.size();
	if (playerSpells[nonActiveSpells[random]].returnManaCost() < Player.Mana && Player.manaSpent < lowestManaCount) {
		playerSpells[nonActiveSpells[random]].CastSpell(false);
	}
}

void playersTurn(bool debug) {
	if (debug) {
		cout << endl;
		cout << "-- Player Turn --" << endl;
		cout << "Player has " << Player.HP << " HP, " << Player.Armor << " Armor, " << Player.Mana << " Mana." << endl;
		cout << "Boss has " << Boss.HP << " HP." << endl;
	}
	
	for (int i = 0; i < playerSpells.size(); i++) {
		if (playerSpells[i].isActive()) {
			playerSpells[i].CastSpell(true);
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
		int BossDamage = (Boss.Damage - Player.Armor) > 0 ? Boss.Damage - Player.Armor : - 1;
		Player.HP = Player.HP - BossDamage;
		if (debug) cout << "Boss Deals " << BossDamage << " Damage." << endl;
	}
}

void reset(bool debug) {
	//Player.HP = 50, Player.Mana = 500, Player.Armor = 0;
	//Boss.HP = 55, Boss.Damage = 8;
	Player.HP = 10, Player.Mana = 250, Player.Armor = 0;
	Boss.HP = 13, Boss.Damage = 8;
	playerSpells.clear();
	playerSpells.push_back(Spell("Magic Missile", 53, 1, 4, debug));
	playerSpells.push_back(Spell("Drain", 73, 1, 2, debug));
	playerSpells.push_back(Spell("Shield", 113, 7, 7, debug)); //Shield is 7 instead of 6 turns here, due to the way this is coded, it works out at 6 turns though
	playerSpells.push_back(Spell("Poison", 173, 6, 3, debug));
	playerSpells.push_back(Spell("Recharge", 229, 5, 101, debug));
}

int main() {
	bool debug = true;

	reset(debug);
	srand(time(NULL));

	for (int i = 0; i < 1; i++) {
		reset(debug);
		while (Player.HP > 0 && Boss.HP > 0) {
			if (Player.Mana < 53) break;
			playersTurn(debug);
			bossTurn(debug);
		}

		if (Boss.HP <= 0) {
			if (Player.manaSpent < lowestManaCount) {
				lowestManaCount = Player.manaSpent;
			}
			cout << "Player Won";
		}
	}

	cout << lowestManaCount;
	cin.get();
}