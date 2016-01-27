#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

const int codeRow = 2981;
const int codeColumn = 3075;
const int ArraySize = 10000;

double paperArray[ArraySize][ArraySize];

double previousValue = 20151125;
double multiplyValue = 252533;
double divideValue = 33554393;


int main() {

	paperArray[0][0] = previousValue;
	
	int nDiags = ArraySize + ArraySize - 1;

	for (int diag = 0; diag < nDiags; diag++) {
		int rowStop = max(0, diag - ArraySize + 1);
		int rowStart = min(diag, ArraySize - 1);
		for (int row = rowStart; row >= rowStop; row--) {
			int col = diag - row;
			if (row > 0 || col > 0) {
				double newValue = fmod(previousValue * multiplyValue, divideValue);
				paperArray[row][col] = newValue;
				previousValue = newValue;
			}
			

		}
	}

	cout.precision(17);
	cout << "Code is: " << fixed << paperArray[codeRow - 1][codeColumn - 1];

	cin.get();
}