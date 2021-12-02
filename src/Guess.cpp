#include "Guess.h"

Guess::Guess(RowCol _square, char _guess,SUDOKUTYPE _state) {
    memcpy(state, _state, sizeof(SUDOKUTYPE));
    square = _square;
	guess = _guess;
}

Guess::Guess() {
    for(int16_t r = 0 ; r < 9 ; r++) {
        for(int16_t c = 0 ; c < 9 ; c++) {
            state[r][c].value = '\0';
            state[r][c].allowableValues[0] = '\0';
        }
    }
	square = RowCol();
	guess = '\0';
}
Guess::Guess(const Guess& g) {
    memcpy(state, g.state, sizeof(SUDOKUTYPE));
	square = g.square;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
    memcpy(state, cpy.state, sizeof(SUDOKUTYPE));
    square = cpy.square;
	guess = cpy.guess;
	return *this;
}

string Guess::toString() {
	char ss[1000];
    sprintf(ss,"Square: %s, Guess: %c,\n",square.toString(), guess);
	string retval;
	return retval;
}