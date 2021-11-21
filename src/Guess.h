#ifndef _GUESS_H
#define _GUESS_H
#pragma once

#include <string>
#include <cstring>

using namespace std;

#include "SudokuTypes.h"

class Guess
{
public:
	Guess(sudokuType _state, ROWCOL _square, char _guess);
	Guess();
	Guess(const Guess&);
	~Guess();
	Guess& operator=(const Guess& cpy) ;

	char* toString();
	void toString(char* ans);

	static ROWCOL* textToRC(const char* text);
	static char* RCToText(ROWCOL rc);

	sudokuType& getState();
	void setState(sudokuType);
	//////////////////////////////////////////////////////////////

	sudokuType state;
	ROWCOL rc;
	char guess;

};

#endif // _GUESS_H

