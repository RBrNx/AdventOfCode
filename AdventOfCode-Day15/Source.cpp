#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void swap(int places[], int i, int j) {
	int temp = 0;
	temp = places[i];
	places[i] = places[j];
	places[j] = temp;
}

void perm(int combo[], int n, int i) {
	if (i == n) {
		for (int i = 0; i < 4; i++) {
			cout << combo[i] << "  ";
		}
		cout << endl;
	}
	else {
		for (int j = i; j < n; j++) {
			swap(combo, i, j);
			perm(combo, n, i + 1);
			swap(combo, i, j);
		}
	}
}

int main() {
	int ints[4];

	for (int i = 0; i < 4; i++) {
		ints[i] = i;
	}

	perm(ints, 4, 0);

	cout << "Program Finshed";
	cin.get();
}