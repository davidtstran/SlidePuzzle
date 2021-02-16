// David Tran 
// CS461 
// Program 1
// Unguided Search to Solve a Game Problem (3x3 Slide Puzzle) 

// Algo
	// from E, find lowest solve score (# of inversions to get win case)
	// shift with lowest score, then continue until get win condition
	// unsolvable if : odd inversions to get to 1 2 3 4 5 6 7 8 

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Puzzle.h"
using namespace std;

int main() {
	string inputFile = "prog1_input.txt";
	ifstream fin(inputFile);
	//ifstream fin("test_input.txt");

	if (fin.fail()) {
		cout << inputFile << " File Not Found\n";
		getchar();
		return 0;
	}

	int puzzleCount;
	fin >> puzzleCount;
	for (int numPuz = 0; numPuz < puzzleCount; numPuz++) { // solve puzzle 1 by 1
		char puzzl[9] = {};
		for (int i = 0; i < 9; i++) {
			fin >> puzzl[i];
		}
		Puzzle p(puzzl);
		char solnPuz[9] = { '1','2','3','4','5','6','7','8','E' };
		Puzzle soln(solnPuz);
		p.printPuzzle();
		if (p.solvable()) {
			vector<Puzzle> prevStates;
			int steps = 1;
			while (p != soln) {
				cout << "Step " << steps << ": ";
				p = p.solve(prevStates);
				p.printInLine();
				steps++;
			}
		}
		else
			cout << "This Puzzle is Not Solvable.\n";
		cout << endl;
	}

	fin.close();
	cout << "\nEnd of Program. Press to Close.";
	getchar();
	return 0;
}