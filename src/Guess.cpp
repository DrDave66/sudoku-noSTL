#include "Guess.h"

Guess::Guess(RowCol _square, char _guess, char* _puzzle, char* _allowableValues) {
    memcpy(puzzle, _puzzle , 81);
    memcpy(allowableValues, _allowableValues, 810);
    square = _square;
	guess = _guess;
}

Guess::Guess() {
    for(int16_t r = 0 ; r < 9 ; r++) {
        for(int16_t c = 0 ; c < 9 ; c++) {
            puzzle[r][c] = '\0';
            allowableValues[r][c][0] = '\0';
        }
    }
	square = RowCol();
	guess = '\0';
}
Guess::Guess(const Guess& g) {
    memcpy(puzzle, g.puzzle , 81);
    memcpy(allowableValues, g.allowableValues, 810);
    square = g.square;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
    memcpy(puzzle, cpy.puzzle , 81);
    memcpy(allowableValues, cpy.allowableValues, 810);
    square = cpy.square;
	guess = cpy.guess;
	return *this;
}

string Guess::toString() {
    char ss[1000];
    sprintf(ss,"Square: %s, Guess: %c,\n",square.toString(), guess);
    return string(ss);
}