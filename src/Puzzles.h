#ifndef _PUZZLES_H
#define _PUZZLES_H

#pragma once

#include <stdint.h>
#include <iostream>
#include <cstring>

using namespace std;

class Puzzles
{
public:
	Puzzles();
	Puzzles(const char* fname);
	~Puzzles();
	uint32_t getNumberOfPuzzles(void);
	char* getPuzzle(uint32_t num);

private:

	char** c_puzzles;
	char filename[300];
	uint32_t numPuzzles;
};

#endif //_PUZZLES_H