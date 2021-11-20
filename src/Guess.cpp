#include "Guess.h"
#include "Sudoku.h"



Guess::Guess(sudokuType _state, RowCol _square, char _guess) {
	memcpy(state, _state, sizeof(sudokuType));
	rc.row = _square.row;
	rc.col = _square.col;
	guess = _guess;
}

Guess::Guess() {
	rc.row = 0;
	rc.col = 0;
	guess = '0';
}
Guess::Guess(const Guess& g) {
	memcpy(state, g.state, sizeof(sudokuType));
	rc.row = g.rc.row;
	rc.col = g.rc.col;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
	memcpy(state, cpy.state, sizeof(sudokuType));
	rc.row = cpy.rc.row;
	rc.col = cpy.rc.col;
	guess = cpy.guess;
	return *this;
}

Guess::~Guess() {
}

sudokuType& Guess::getState() {
	return state;
}
void Guess::setState(sudokuType st) {
	memcpy(state, st, sizeof(sudokuType));
}
char* Guess::toString() {
	static char ss[60];
    sprintf(ss,"Square: %s, Guess: %c",RowCol::toText(rc), guess);
	return ss;
}

void Guess::toString(char* ans) {
	char* ts = toString();
	strncpy(ans, ts, strlen(ts));
}


