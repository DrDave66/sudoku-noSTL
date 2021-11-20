#ifndef _SUDOKU_H
#define _SUDOKU_H

#pragma once

#include <typeinfo>
//#include <string>
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
    void printPuzzle(sudokuType state);
    void printPuzzle(void);
    void printPuzzle(char* title);
    void printAllowableValues(void);
	void printAllowableValues(char* title);
	void printAllowableValues(sudokuType state);
    
    // solving funcitons
    //bool setValue(string square, string value);
    bool setValue(uint32_t r, uint32_t c, char value);
    bool setValue(RowCol rc, char value);
    bool setValue(Guess);
	void removeChar(char* str, char ch);
	uint32_t countOccurrences(char* str, char ch);
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
    bool popGuess();
    bool pushGuess(const Guess);
    
	char* getAllowableValuesText(void);
	char* getPuzzleText(void);
	
//	string printableStringVector(vector<string> vec);
//	string printableVectorVectorString(vector<vector<string> >);
//	string printableStringSet(set<string> st);
//set<string> digitSet = { "1","2","3","4","5","6","7","8","9" };



	void test();

	void printSudoku();
	void printSudoku(sudokuType); // so you can look into the guess stack

    sudokuType sudoku;

	vector<string> crossProduct(string a, string b);
	static const uint32_t numRows = 9;
	static const uint32_t numCols = 9;


	const char* c_digits = "123456789";
	const char* c_rows = "ABCDEFGHI";
	const char* c_cols = "123456789";

	static const uint32_t dimNumUnitLists = 27;
	static const uint32_t dimNumElementsInUnitList = 9;
	RowCol c_unitList[dimNumUnitLists][dimNumElementsInUnitList];
	
	static const uint32_t dimNumSquaresPerUnit = 9;
	static const uint32_t dimNumUnits = 3;

	static const uint32_t dimNumPeers = 20;
    
    uint32_t dimNumDigits = 9;
    string digits = "123456789";
    string rows = "ABCDEFGHI";
    string cols = "123456789";
    
    
    static const uint32_t guessStackDepth = 81;
    Guess guessStack[guessStackDepth];
    uint32_t currentGuess = 0;
    Guess newGuess;
    
    //ROWCOL c_squares[numRows][numCols];
    //ROWCOL c_units[numRows][numCols][dimNumUnits][dimNumSquaresPerUnit];
    // we do not use c_units - they are placed in sudokuType
	//ROWCOL c_peers[numRows][numCols][dimNumPeers];
	// we do not use c_peers - they are placed in sudokuType

    //	static const size_t valueStringLength = 81 * 11 + 1;
    //	static const size_t puzzleStringLength = 82;
    
    //	char c_puzzle[numRows][numCols];
    //	static const uint32_t allowableDimLen = 10;
    //	char c_allowableValues[numRows][numCols][allowableDimLen];
    //map<string, string> puzzle; // unit, value


	//map<string, string> allowableValues; // square, string of allowable values
	//vector<Guess> guessList; // ordered list of guesses


};

#endif //_SUDOKU_H
