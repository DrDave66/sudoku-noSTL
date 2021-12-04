#include "Sudoku.h"
#define NOTIMING

Sudoku::Sudoku() {
	createVectors();
	clearPuzzle();
	srand((uint32_t)time(NULL));
}

Sudoku::Sudoku(const char* puzzle) {
	createVectors();
	setPuzzle(puzzle);
	srand((uint32_t)time(NULL));
}

void Sudoku::createVectors(void) {
	vector<string> stlsquares;
	vector<vector<string> > stlunitlist;
	map<string, vector<vector<string> > > stlunits; // square, squares in unit
	map<string, vector<string> > stlpeers; // square, squares in peers
	// create vector of squares
	stlsquares = crossProduct(rows, cols);
	// create unitlist vector
	vector<string> temp;
	// for each col across the rows
    string scols = "123456789";
    string srows = "ABCDEFGHI";
    for (auto c : scols) {
		temp = crossProduct(rows, string(1, c));
		stlunitlist.push_back(temp);
	}
	// for each row across the cols
    for (auto r : srows) {
		temp = crossProduct(string(1, r), cols);
		stlunitlist.push_back(temp);
	}
	// for each 9x9 square
	vector<string> sr = { "ABC","DEF","GHI" };
	vector<string> sc = { "123", "456", "789" };
	for (string r : sr) {
		for (string c : sc) {
			temp = crossProduct(r, c);
			stlunitlist.push_back(temp);
		}
	}
    
	// make unit dictionary - all units that contain the square
	for (string sq : stlsquares) {
		vector<vector<string> > tempUnitList;
		tempUnitList.clear();
		for (vector<string> ul : stlunitlist) {
			for (string l : ul) {
				if (l == sq) {
					tempUnitList.push_back(ul);
				}
			}
		}
		stlunits[sq] = tempUnitList;
	}
	// make peer dictionary
	for (string s : stlsquares) {
		set<string> vec; // use a set so there are no duplicates
		for (vector<string> u : stlunits[s]) {
			for (string l : u) {
				if (l != s) {
					vec.insert(l);
				}
			}
		}
		vector<string> v(vec.begin(), vec.end());
		stlpeers[s] = v;
	}

	// now use the STL vectors to populate the non-stl stuff

	// unitlists
	for (uint8_t ul = 0; ul < dimNumUnitLists; ul++) {
		for (uint8_t i = 0; i < dimNumSquaresPerUnit;i++) {
			workrc.fromString(stlunitlist[ul][i]);
            unitList[ul][i] = workrc;
		}
	}
 
	// units
	RowCol rrcc;
	for (int r = 0; r < numRows ; r++) {
		for (int c = 0; c < numCols ; c++) {
			for (int nu = 0; nu < dimNumUnits ; nu++) {
				for (int s = 0; s < dimNumSquaresPerUnit; s++) {
					rrcc.row = r;
					rrcc.col = c;
					workrc.fromString(stlunits[rrcc.toString()][nu][s]);
					//c_units[r][c][nu][s] = rc;
					units[r][c][nu][s] = workrc;
				}
			}
		}
	}
    
    // peers
	for (int r = 0; r < numRows; r++) {
		rrcc.row = r;
		for (int c = 0; c < numCols; c++) {
			rrcc.col = c;
			for (int np = 0; np < dimNumPeers; np++) {
				workrc.fromString(stlpeers[rrcc.toString()][np]);
				peers[r][c][np] = workrc;
			}
		}
	}

#if 0

    printf("\n\nUNITLIST\n");
    for (uint8_t ul = 0; ul < dimNumUnitLists; ul++) {
        for (uint8_t i = 0; i < dimNumSquaresPerUnit;i++) {
            printf("%s ",unitList[ul][i].toString());
        }
        printf("\n");
    }
    printf("\n\nUNITS\n");
    for (int r = 0; r < numRows ; r++) {
        for (int c = 0; c < numCols ; c++) {
            printf("%c%c:\n",r+'A',c+'1');
            for (int nu = 0; nu < dimNumUnits ; nu++) {
                for (int s = 0; s < dimNumSquaresPerUnit; s++) {
                    printf("%s ",units[r][c][nu][s].toString());
                }
                printf("\n");
            }
            printf("\n");
        }
        
    }
    printf("\n\nPEERS\n");
    for (int r = 0; r < numRows ; r++) {
        for (int c = 0; c < numCols ; c++) {
            printf("%c%c:\n",r+'A',c+'1');
            for (int np = 0; np < dimNumPeers; np++) {
                rc.fromString(stlpeers[rrcc.toString()][np]);
                printf("%s ",peers[r][c][np].toString());
            }
            printf("\n");
        }
        
    }
#endif
    //	int jj = 0;
}

vector<string> Sudoku::crossProduct(string a, string b) {
    vector<string> v;
    string s;
    for (auto aa : a) {
        for (auto bb : b) {
            s += aa;
            s += bb;
            v.push_back(s);
            s.clear();
        }
    }
    return v;
}

void Sudoku::clearPuzzle(void) {
	for( uint8_t r = 0 ; r < 9 ; r++) {
		for (uint8_t c = 0; c < 9; c++) {
			puzzle[r][c] ='.';
			strncpy(allowableValues[r][c], "123456789", 10);
		}
	}
}


bool Sudoku::setPuzzle(const char* p) {
	if (strlen(p) != 81)
		return false;
	clearPuzzle();
	for (int8_t r = 0; r < numRows; r++) {
		for (int8_t c = 0;c < numCols; c++) {
			setValue(r, c, p[c + r * numCols]);
		}
	}
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/

void Sudoku::printPuzzle(char* title) {
    printf("%s",title);
	printPuzzle();
}

void Sudoku::printPuzzle() {
	char header[] =  "     1   2   3    4   5   6    7   8   9";
		char top[] = "  =========================================";
	char row_sep[] = "  || --------- || --------- || --------- ||";
	char col_sep[] = "||";
	char num_sep[] = "|";
	cout << endl << header << endl;
	cout << top << endl;
	for (uint32_t r = 0; r < numRows; r++) {
		cout << rows[r] << " " << col_sep;
		for (uint32_t c = 0; c < numCols; c++) {
			if (puzzle[r][c] == '0') {
				cout << "  ";
			}
			else {
                cout << " " << puzzle[r][c];
			}
			if (c > 0 && (c + 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
		}
		cout << endl;
		if (r == numRows -1 ) {
			cout << top << endl;
		}
		else if ((r + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

void Sudoku::printAllowableValues() {
	char header[] = "         1           2           3            4           5           6            7           8           9";
	//char header[] = "         0           1           2            3           4           5            6           7           8";
	char top[] = "  =================================================================================================================";
	char row_sep[] = "  || --------------------------------- || --------------------------------- || --------------------------------- ||";
	char col_sep[] = "||";
	char num_sep[] = "|";
	cout << endl << header << endl;
	cout << top << endl;
	string index;
	for (uint32_t r = 0; r < numRows; r++) {
		cout << rows[r] << " " << col_sep;
		//cout << r << " " << col_sep;
		for (uint32_t c = 0; c < numCols; c++) {
			cout << " " << setw(9) << allowableValues[r][c];
			if (c > 0 && (c + 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
		}
		cout << endl;
		if (r == 8) {
			cout << top << endl;
		}
		else if ((r + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

void Sudoku::printAllowableValues(char* title) {
    printf("%s",title);
	printAllowableValues();
}

/**********************************************************
**********   Solving Functions ***************************
***********************************************************/

uint8_t Sudoku::countOccurrences(char* str, char ch) {
	uint8_t count = 0;
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
		{
			count++;
		}
		i++;
	}
	return count;

}

void Sudoku::removeChar(char* str, char ch) {
	uint32_t i, j;
	size_t len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == ch)
		{
			for (j = i; j < len; j++)
			{
				str[j] = str[j + 1];
			}
			len--;
			i--;
		}
	}
}

void Sudoku::removeFirstChar(char* str, char ch) {
    uint32_t i, j;
    size_t len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == ch)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            return;
        }
    }
}

bool Sudoku::setValue(uint8_t r, uint8_t c, char value) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
    uint8_t rr,cc;
//
	if (value == '0' || value == '.') {
        puzzle[r][c] = '.';
        return true;
	}
	else {
        if (countOccurrences(allowableValues[r][c], value) == 0)
            return false;
		allowableValues[r][c][0] = '\0';
        puzzle[r][c] = value;
    }

	for (uint8_t p = 0; p < dimNumPeers; p++) {
		rr = peers[r][c][p].row;
        cc = peers[r][c][p].col;
		removeChar(allowableValues[rr][cc], value);
	}
#ifdef TIMING
	ptl.stop();
	cout << "setValue," << ptl.elapsedString() << endl;
#endif
	return true;
}

bool Sudoku::solveOnes(void) {
#ifdef TIMING	
	PrecisionTimeLapse ptl;
	ptl.start();
#endif	

	bool solvedSome = true; // set to true to ensure one iteration
	while (solvedSome == true) {
        solvedSome = false; // set to false to exit after one interation if nothing is set
        // find squares with only one available value
        for (uint8_t r = 0; r < numRows; r++) {
            for (uint8_t c = 0; c < numCols; c++) {
                if (strlen(allowableValues[r][c]) == 1) {
                    setValue(r, c, (char)allowableValues[r][c][0]);
                    solvedSome = true;
                }
            }
        }
        // look through all units and see if any value appears only one time

        for (uint8_t ul = 0; ul < dimNumUnitLists; ul++) {
            allValues[0] = '\0';
            for (uint8_t s = 0; s < dimNumElementsInUnitList; s++) {
                workrc = unitList[ul][s];
                strcat(allValues, allowableValues[unitList[ul][s].row][unitList[ul][s].col]);
            }
            // count to see if any value only appears one time in a unit
            for (uint32_t d = 0; d < dimNumDigits;d++) {
                if (countOccurrences(allValues, digits[d]) == 1) {
                    for (uint32_t s = 0; s < dimNumElementsInUnitList; s++) {
                        if (countOccurrences(allowableValues[unitList[ul][s].row][unitList[ul][s].col], digits[d]) == 1) {
                            setValue(unitList[ul][s], digits[d]);
                            solvedSome = true;
                            break;
                        }
                    }
                }
            }
        }
        
	}

#ifdef TIMING	
	ptl.stop();
	cout << "solveOnes," << ptl.elapsedString() << endl;
#endif
	return solvedSome;
}

bool Sudoku::isPuzzleSolved(void) {
//	// a puzzle is solved if each unit in unitlist contains values of 1-9
	char unitValues[10];

	// first check - get puzzle text and look for '.'
	for (uint8_t ul = 0; ul < dimNumUnitLists;ul++) {
		for (uint8_t u = 0; u < dimNumElementsInUnitList; u++) {
			unitValues[u] = puzzle[unitList[ul][u].row][unitList[ul][u].col];
		}
		unitValues[9] = '\0';
		// string is built.  make sure each digit appears exactly once
        for (uint8_t i = 0; i < 9; i++) {
            if (strchr(unitValues, digits[i]) == NULL)
                return false;
        }
	}
	return true;

}

bool Sudoku::removeAllowableValue(uint8_t r, uint8_t c, char value) {
    bool retval;
    char* pstr = allowableValues[r][c];
    if(strchr(pstr, value) == NULL) {
        retval = false;
    } else {
        removeFirstChar(pstr,value);
        retval = true;
    }
    return retval;
}

bool Sudoku::removeAllowableValue(RowCol rc, char value) {
    return removeAllowableValue(rc.row, rc.col, value);
}

bool Sudoku::removeAllowableValue(Guess g) {
    return removeAllowableValue(g.square.row, g.square.col, g.guess);
}
bool Sudoku::guessesRemain(void) {
	for (uint8_t r = 0; r < numRows; r++) {
		for (uint8_t c = 0; c < numCols; c++) {
			if (strlen(allowableValues[r][c]) > 0)
				return true;
		}
	}
	return false;
}

Guess Sudoku::getGuessNotRandom() {
//    size_t minCount = 9;
//    // iterate through squares and get lowest count > 1
//    size_t len;
//    ROWCOL rc[81];
//    uint32_t numFound = 0;
//    // search through all squares and find minimum number of availableValues
//    for(uint32_t r = 0 ; r < numRows ; r++) {
//        for (uint32_t c = 0 ; c < numCols ; c++) {
//            len = strlen(sudoku[r][c].allowableValues);
//            if(len != 0) {
//                minCount = min(minCount, len);
//            }
//        }
//    }
//    // make a list of all squares with the mininum values
//    for(uint32_t r = 0 ; r < numRows ; r++) {
//        for (uint32_t c = 0 ; c < numCols ; c++) {
//            len = strlen(sudoku[r][c].allowableValues);
//            if(len == minCount) {
//                rc[numFound].row = r;
//                rc[numFound].col = c;
//                numFound++;
//            }
//        }
//    }
//    // pick first RC and first value
//    ROWCOL rcg = rc[0];
//    // now pick random number
//    char* pstr = sudoku[rcg.row][rcg.col].allowableValues;
//    char g = pstr[0];
//    newGuess = Guess(sudoku,rcg,g);
    return newGuess;
}

Guess Sudoku::getGuessNoMin() { // returns Guess, but does not look at the number of avaiable guesses in each square
    //	size_t len;
    //	ROWCOL rc[81];
    //	uint32_t numFound = 0;
    //	// make a list of all squares with the mininum values
    //	for (uint32_t r = 0; r < numRows; r++) {
    //		for (uint32_t c = 0; c < numCols; c++) {
    //			len = strlen(sudoku[r][c].allowableValues);
    //			if (len > 0) {
    //				rc[numFound].row = r;
    //				rc[numFound].col = c;
    //				numFound++;
    //			}
    //		}
    //	}
    //	// pick one
    //	ROWCOL rcg = rc[rand() % numFound];
    //	// now pick random number
    //	char* pstr = sudoku[rcg.row][rcg.col].allowableValues;
    //	char g = pstr[rand() % strlen(pstr)];
    return newGuess;
}

Guess Sudoku::getGuess() { // returns Guess
	size_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;

    uint8_t numFound = 0;
    // search through all squares and find minimum number of availableValues
    for(uint8_t r = 0 ; r < numRows ; r++) {
        for (uint8_t c = 0 ; c < numCols ; c++) {
            len = strlen(allowableValues[r][c]);
            if(len != 0) {
                minCount = min(minCount, len);
            }
        }
    }
    // make a list of all squares with the mininum values
    for(uint8_t r = 0 ; r < numRows ; r++) {
        for (uint8_t c = 0 ; c < numCols ; c++) {
            len = strlen(allowableValues[r][c]);
            if(len == minCount) {
                rcGuess[numFound].row = r;
                rcGuess[numFound].col = c;
                numFound++;
            }
        }
    }
    // pick one
    workrc = rcGuess[rand() % numFound];
    // now pick random number
    char* pstr = allowableValues[workrc.row][workrc.col];
    char g = pstr[rand() % strlen(pstr)];
    newGuess = Guess(workrc, g, (char*)puzzle, (char*)allowableValues);
    return newGuess;
}


bool Sudoku::popGuess() {
    if(currentGuess == 0)
        return false;
    Guess lastGuess = guessStack[currentGuess-1];
    memcpy(puzzle, lastGuess.puzzle, 81);
    memcpy(allowableValues, lastGuess.allowableValues, 810);
    removeAllowableValue(lastGuess);
    currentGuess--;
    return true;
}

bool Sudoku::pushGuess(const Guess guess) {
    if (currentGuess >= guessStackDepth)
        return false;
    else
    {
        memcpy(&guessStack[currentGuess],&guess,sizeof(Guess));
        currentGuess++;
        return true;
    }
}

void Sudoku::printGuessList() {
    if(currentGuess == 0) {
        printf("No Guesses in Stack\n");
    }else {
        for (uint8_t g = 0 ; g < currentGuess ; g++) {
            //printf("%s <- %c ",Guess::RCToText(guessStack[g].rc), guessStack[g].guess);
            if (g != currentGuess -1) {
                printf(": ");
            }
        }
        printf("\n");
    }
}

bool Sudoku::solvePuzzle() {
    solveOnes();
	if (isPuzzleSolved())
		return true;
	else 
		return startGuessing();
}
bool Sudoku::setValue(RowCol rc, char value) {
    return setValue(rc.row, rc.col,value);
}

bool Sudoku::setValue(Guess g) {
    return setValue(g.square.row, g.square.col, g.guess);
    
}
static int ggg;

bool Sudoku::startGuessing() {
    currentGuess = 0;
    ggg = 0;
    while(!isPuzzleSolved()) {
        while(guessesRemain()) {
            //ggg++;
            //Guess g = getGuessNotRandom();
            Guess g = getGuess();
            //Guess g = getGuessNoMin();
            pushGuess(g);
            setValue(g);
            solveOnes();
            if ( !isPuzzleSolved() && !guessesRemain()) {
                popGuess();
            }
            //if(ggg % 50000 == 0)
            //    printf("%d - %d\n",ggg,currentGuess);
        }

        if( !isPuzzleSolved()) {
            if (popGuess() == false)
                return false;
        }
    }
    //printf("Guesses %d\n",ggg);
    return isPuzzleSolved();
}


void Sudoku::test(void) {


}
