#include "Puzzles.h"
#include "PrecisionTimeLapse.h"

Puzzles::Puzzles() {
	cout << "blank constructor\n";
	numPuzzles = 0; 
	strncpy(filename, "", 1);
} 

Puzzles::Puzzles(const char*  fname) {
	strncpy(filename, fname, strlen(fname));
	char filename[300]; 
	PrecisionTimeLapse ptl;
	cout << fname << endl;
	ptl.start();
	strncpy(filename, fname,300);

	char line[83];
	FILE* f = fopen(filename,"rt");
	if (f == NULL) {
		printf("File %s not found\n", filename);
		return;
	}
	uint32_t i;
	numPuzzles = 0;
	while (fgets(line, 83, f) != NULL) {
        if(strncmp(line,"\n",1) != 0)
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
        if(strncmp(line,"\n",1) != 0) {
            strncpy(c_puzzles[i], line, 81);
            c_puzzles[i][81] = '\0';
            i++;
        }
	}
	ptl.stop();
	printf("%f sec\n", ptl.elapsed());
}

Puzzles::~Puzzles() {
	uint32_t i;
	for (i = 0; i < numPuzzles; i++) {
		delete[] c_puzzles[i];
	}
	delete[] c_puzzles;
}
uint32_t Puzzles::getNumberOfPuzzles(void) {
	return numPuzzles;
}

char* Puzzles::getPuzzle(uint32_t num) {
	return c_puzzles[num];
}

