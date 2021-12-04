#pragma once
#ifndef _GUESS
#define _GUESS

#include <string>
#include <cstring>
using namespace std;
#include "RowCol.h"
#include "SudokuTypes.h"

class Sudoku;

class Guess
{
public:
	Guess(RowCol _square, char _guess, char* _puzzle, char* _allowableValues);

    Guess();
	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();

    char puzzle[9][9];
    char allowableValues[9][9][10];

	RowCol square;
	char guess;
};

#endif // _GUESS

