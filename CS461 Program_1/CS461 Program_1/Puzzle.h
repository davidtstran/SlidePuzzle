#pragma once
// David Tran 
// CS461 
// Program 1
// Unguided Search to Solve a Game Problem (3x3 Slide Puzzle) 

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Puzzle {
private:
	char puz[9] = {};
	map <int, vector<int>> possibleMoves;

public:
	Puzzle();
	Puzzle(char newPuz[9]);
	void createPossibleMoves();

	char valAtIndex(int idx);
	bool solvable();
	Puzzle solve(vector<Puzzle> &vect); // visit first with lowest hScore
	int hScore(); // Manhattan Distance + Number of Tiles Out of Place
	void printPuzzle();
	void printInLine();

	bool operator==(Puzzle rhs);
	bool operator!=(Puzzle rhs);


};