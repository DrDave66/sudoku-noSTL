#pragma once
#ifndef _SUDOKUTYPES_H
#define _SUDOKUTYPES_H

using namespace std;

#include "RowCol.h"
//
//struct ROWCOL {
//	uint8_t row;
//	uint8_t col;
//};

struct SQUARE {
	char name[3];
	char value;
	char allowableValues[10];
	RowCol units[3][9];
	RowCol peers[20];
};

typedef SQUARE sudokuType[9][9]; // 8748 types

#endif // _SUDOKUTYPES_H