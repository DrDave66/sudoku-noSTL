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
	Guess(RowCol _square, char _guess, SUDOKUTYPE _state);

    Guess();
	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();

    SUDOKUTYPE state;

	RowCol square;
	char guess;
};

#endif // _GUESS

