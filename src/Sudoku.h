#ifndef _SUDOKU_H
#define _SUDOKU_H

#pragma once

#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "SudokuTypes.h"
#include "Guess.h"
#include "RowCol.h"

class Sudoku
{
public:
	Sudoku();
	Sudoku(const char* puzzle);
   	bool setPuzzle(const char* p);
	void clearPuzzle();
	void createVectors(void);
    
	// printing functions
    void printPuzzle(SUDOKUTYPE state);
    void printPuzzle(void);
    void printPuzzle(char* title);
    void printAllowableValues(void);
	void printAllowableValues(char* title);
	void printAllowableValues(SUDOKUTYPE state);
    
    // solving funcitons
    bool setValue(uint8_t r, uint8_t c, char value);
    bool setValue(RowCol rc, char value);
    bool setValue(Guess);
	void removeChar(char* str, char ch);
    void removeFirstChar(char* str, char ch);
	uint8_t countOccurrences(char* str, char ch);
	bool solveOnes(void);
    bool isPuzzleSolved(void);
    bool solvePuzzle();
    
    // guessing tree functions
    bool startGuessing();
    void printGuessList();
    bool removeAllowableValue(uint8_t r, uint8_t c, char value);
    bool removeAllowableValue(RowCol rc, char value);
    bool removeAllowableValue(Guess g);
    bool guessesRemain(void);
    Guess getGuess();
	Guess getGuessNoMin();
    Guess getGuessNotRandom();
    bool popGuess();
    bool pushGuess(const Guess);
    
	char* getAllowableValuesText(void);
	char* getPuzzleText(void);
	
//	string printableStringVector(vector<string> vec);
//	string printableVectorVectorString(vector<vector<string> >);
//	string printableStringSet(set<string> st);
	



	void test();

	void printSudoku();
	void printSudoku(SUDOKUTYPE); // so you can look into the guess stack

    static const uint32_t guessStackDepth = 81;
	Guess guessStack[guessStackDepth];
    uint32_t currentGuess = 0;
    
private:

public:
	SUDOKUTYPE sudoku;

protected:


	vector<string> crossProduct(string a, string b);
	static const uint32_t numRows = 9;
	static const uint32_t numCols = 9;
	//RowCol squares[numRows][numCols];
	static const size_t valueStringLength = 81 * 11 + 1;
	static const size_t puzzleStringLength = 82;

	char puzzle[numRows][numCols];
	static const uint32_t allowableDimLen = 10;
	char allowableValues[numRows][numCols][allowableDimLen];
	const char* digits = "123456789";
	const char* rows = "ABCDEFGHI";
	const char* cols = "123456789";

	static const uint32_t dimNumUnitLists = 27;
	static const uint32_t dimNumElementsInUnitList = 9;
	RowCol unitList[dimNumUnitLists][dimNumElementsInUnitList];
	
	static const uint32_t dimNumSquaresPerUnit = 9;
	static const uint32_t dimNumUnits = 3;
	RowCol units[numRows][numCols][dimNumUnits][dimNumSquaresPerUnit];
	
	static const uint32_t dimNumPeers = 20;
	RowCol peers[numRows][numCols][dimNumPeers];
    
    //map<string, string> puzzle; // unit, value
	uint32_t dimNumDigits = 9;
	Guess newGuess;
    RowCol rcGuess[81];
	RowCol workrc;
    char puzzleText[81];
};

#endif //_SUDOKU_H
