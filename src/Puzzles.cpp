#include "Puzzles.h"
#include "Sudoku.h"
#include "PrecisionTimeLapse.h"

Puzzles::Puzzles() {
	cout << "blank constructor\n";
	numPuzzles = 0; 
	strncpy(filename, "", 1);
	c_puzzles = NULL;
	srand((uint32_t)time(NULL));
} 

Puzzles::Puzzles(const char*  fname) {
	strncpy(filename, fname, strlen(fname));
	char filename[300];
	PrecisionTimeLapse ptl;
	cout << fname << endl;
	ptl.start();
	strncpy(filename, fname, 300);
	c_puzzles = NULL;
	char line[83];
	FILE* f = fopen(filename, "rt");
	if (f == NULL) {
		printf("File %s not found\n", filename);
		return;
	}
	uint32_t i;
	numPuzzles = 0;
	while (fgets(line, 83, f) != NULL) {
		if (strncmp(line, "\n", 1) != 0)
			numPuzzles++;
	}
	//printf("Read %d lines\n", numPuzzles);
	// reposition to beginning of file
	fseek(f, 0, SEEK_SET);
	// allocate array for puzzle string
	c_puzzles = new char*[numPuzzles];
	// allocate each char array
	for (i = 0; i < numPuzzles; i++) {
		c_puzzles[i] = new char[82];
	}
	i = 0;
	ptl.stop();
	printf("%f sec\n", ptl.elapsed());
	while (fgets(line, 83, f) != NULL) {
		if (strncmp(line, "\n", 1) != 0) {
			strncpy(c_puzzles[i], line, 81);
			c_puzzles[i][81] = '\0';
			i++;
		}
	}
	ptl.stop();
	printf("%f sec\n", ptl.elapsed());
	srand((uint32_t)time(NULL));
}

Puzzles::~Puzzles() {
	uint32_t i;
	for (i = 0; i < numPuzzles; i++) {
		if(c_puzzles[i] != NULL)
			delete[] c_puzzles[i];
	}
	if(c_puzzles != NULL)
		delete[] c_puzzles;
}
uint32_t Puzzles::getNumberOfPuzzles(void) {
	return numPuzzles;
}

char* Puzzles::getPuzzle(uint32_t num) {
	return c_puzzles[num];
}

uint8_t sumDigits(uint8_t d[9]) {
	uint8_t s = 0;
	for (int i = 0; i < 9; i++) {
		s += d[i];
	}
	return s;
}

void Puzzles::generateRandomPuzzle(Sudoku& s, uint8_t minValues) {
	// put numbers into random puzzle string
	uint8_t valuesSet = 0;
	uint8_t digitSet[9];
	uint32_t i;
	uint8_t sd;
	s.clearPuzzle();

	for (i = 0; i < 9;i++) {
		digitSet[i] = 0;
	}
	sd = sumDigits(digitSet);
	while (valuesSet < minValues || sd < 8) {
		Guess g = s.getGuessNoMin();
		s.setValue(g);
		int guessNum = (char)atoi(&g.guess);
		digitSet[guessNum - 1] = 1;
		valuesSet++;
		sd = sumDigits(digitSet);
		//printf("Setting %s to %c, values %d, digits %d\n", Guess::RCToText(g.rc), g.guess, valuesSet, sd);
	}
	printf(" random puzzle with %d squares filled with %d values\n", valuesSet, sd);
}

//def random_puzzle(self, N = 17) :
//	"""Make a random puzzle with N or more assignments. Restart on contradictions.
//	Note the resulting puzzle is not guaranteed to be solvable, but empirically
//	about 99.8% of them are solvable.Some have multiple solutions."""
//	#self.allowable = dict((s, self.digits) for s in self.squares)
//	self.clear_puzzle()
//	for s in self.shuffled(self.squares) :
//		if not self.set_value(s, random.choice(self.allowable_values[s])) :
//			break
//			ds = [self.puzzle[s] for s in self.squares if len(self.allowable_values[s]) == 0]
//			if len(ds) >= N and len(set(ds)) >= 8 :
//				return ''.join(self.puzzle[s] if len(self.allowable_values[s]) == 0 else '.' for s in self.squares)
//				return self.random_puzzle(N)  ## Give up and make a new puzzle
//