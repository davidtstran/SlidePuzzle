// David Tran 
// CS461 
// Program 1
// Unguided Search to Solve a Game Problem (3x3 Slide Puzzle) 

#include "Puzzle.h"

Puzzle::Puzzle() {
	for (int i = 0; i < 9; i++) {
		puz[i] = '0';
	}
}

Puzzle::Puzzle(char newPuz[9]) {
	for (int i = 0; i < 9; i++) {
		puz[i] = newPuz[i];
	}
	createPossibleMoves();
}

void Puzzle::createPossibleMoves() {
	vector<int> moves1 = { 1, 3 };  // 0: 1 3
	possibleMoves[0] = moves1;

	vector<int> moves2 = { 0, 2, 4 }; // 1: 0 2 4
	possibleMoves[1] = moves2;

	vector<int> moves3 = { 1, 5 }; // 2: 1 5
	possibleMoves[2] = moves3;

	vector<int> moves4 = { 0, 4, 6 }; // 3: 0 4 6
	possibleMoves[3] = moves4;

	vector<int> moves5 = { 1, 3, 5, 7 }; // 4: 1 3 5 7
	possibleMoves[4] = moves5;

	vector<int> moves6 = { 2, 4, 8 }; // 5: 2 4 8
	possibleMoves[5] = moves6;

	vector<int> moves7 = { 3, 7 }; // 6: 3 7
	possibleMoves[6] = moves7;

	vector<int> moves8 = { 4, 6, 8 }; // 7: 4 6 8
	possibleMoves[7] = moves8;

	vector<int> moves9 = { 5, 7 }; // 8: 5 7
	possibleMoves[8] = moves9;
}

char Puzzle::valAtIndex(int idx) {
	return puz[idx];
}

bool Puzzle::solvable() {
	int testPuz[8] = {}; // remove E 
	int cnt = 0;
	for (int i = 0; i < 9; i++) {
		if (puz[i] != 'E')
			testPuz[cnt++] = puz[i] - '0';
	}

	int inversCount = 0; // # of swaps to chronological order = # of inversions
	for (int i = 0; i < 8; i++) {
		if (testPuz[i] != (i + 1)) {
			for (int j = 0; j < 8; j++) {
				if (testPuz[j] == (i + 1)) {
					int temp = testPuz[i];
					testPuz[i] = testPuz[j];
					testPuz[j] = temp;
					inversCount++;
				}
			}
		}
	}

	if (inversCount % 2 == 0)
		return true;
	else
		return false;
}

Puzzle Puzzle::solve(vector<Puzzle> &vect) { // visit first with lowest hScore
	int ePos;
	for (int i = 0; i < 9; i++) {
		if (puz[i] == 'E')
			ePos = i;
	}

	int lowScore = 999; // random high number
	int lowPos = 0;
	vect.push_back(*this);
	for (int i = 0; i < possibleMoves[ePos].size(); i++) { // go to first lowest 
		char val = puz[ePos];
		puz[ePos] = puz[possibleMoves[ePos][i]];
		puz[possibleMoves[ePos][i]] = val;
		int previous = false;
		for (int i = 0; i < vect.size(); i++) {
			if (*this == vect[i]){
				previous = true;
				break; // stop searching through once one is found
			}
		}
		if (previous != true) { // if already visited state, go on to next 
			if (hScore() < lowScore) {
				lowScore = hScore();
				lowPos = possibleMoves[ePos][i];
			}
		}
		val = puz[ePos];
		puz[ePos] = puz[possibleMoves[ePos][i]];
		puz[possibleMoves[ePos][i]] = val;
	}
	int val = puz[ePos];
	puz[ePos] = puz[lowPos];
	puz[lowPos] = val;
	cout << "Swap E for " << puz[ePos] << ": ";
	return *this;
}

int Puzzle::hScore() { // Manhattan Distance + Number of Tiles Out of Place
	map <int, pair<int, int>> posValues;
	posValues[0] = make_pair(1, 1);
	posValues[1] = make_pair(1, 2);
	posValues[2] = make_pair(1, 3);
	posValues[3] = make_pair(2, 1);
	posValues[4] = make_pair(2, 2);
	posValues[5] = make_pair(2, 3);
	posValues[6] = make_pair(3, 1);
	posValues[7] = make_pair(3, 2);
	posValues[8] = make_pair(3, 3);

	int score = 0;
	for (int i = 0; i < 9; i++) {
		if (puz[i] != 'E') {
			if (puz[i] - '0' != (i + 1)) {
				score += 1; // if number is out of place, add 1 by default, then add manhattan distance
				score += abs(posValues[i].first - posValues[puz[i] - '0' - 1].first);
				score += abs(posValues[i].second - posValues[puz[i] - '0' - 1].second);
			}
		}
	}

	return score;
}

void Puzzle::printPuzzle() {
	for (int i = 0; i < 7; i+=3) {
		for (int j = 0; j < 3; j++) {
			cout << puz[j + i] << " ";
		}
		cout << endl;
	}
}

void Puzzle::printInLine() {
	for (int i = 0; i < 9; i++) {
		cout << puz[i] << " ";
	}
	cout << endl;
}

bool Puzzle::operator==(Puzzle rhs) {
	for (int i = 0; i < 9; i++) {
		if (this->puz[i] != rhs.valAtIndex(i))
			return false;
	}
	return true;
}

bool Puzzle::operator!=(Puzzle rhs) {
	for (int i = 0; i < 9; i++) {
		if (this->puz[i] != rhs.valAtIndex(i))
			return true;
	}
	return false;
}