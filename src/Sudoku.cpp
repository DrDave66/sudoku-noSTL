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

string getPrintableStringVector(vector<string> vec) {
    string retval;
    for(string s : vec) {
        retval += s + " ";
    }
    return retval;
}

string getPrintableVectorVectorString(vector<vector<string> > vec) {
    string retval;
    for (vector<string> vs : vec) {
        for (string s : vs) {
            retval += s + " ";
        }
        retval += "\n";
    }
    return retval;
}

void Sudoku::createVectors(void) {
	vector<string> squares;
	vector<vector<string> > unitlist;
	map<string, vector<vector<string> > > units; // square, squares in unit
	map<string, vector<string> > peers; // square, squares in peers
	// create vector of squares
	squares = crossProduct(rows, cols);
	// create unitlist vector
//    cout << getPrintableStringVector(squares) << endl << endl;
    
	vector<string> temp;
	// for each col across the rows
	for (char c : cols) {
		temp = crossProduct(rows, string(1, c));
		unitlist.push_back(temp);
	}
	// for each row across the cols
	for (char r : rows) {
		temp = crossProduct(string(1, r), cols);
		unitlist.push_back(temp);
	}
	// for each 9x9 square
	vector<string> sr = { "ABC","DEF","GHI" };
	vector<string> sc = { "123", "456", "789" };
	for (string r : sr) {
		for (string c : sc) {
			temp = crossProduct(r, c);
			unitlist.push_back(temp);
		}
	}
//    cout << "unit list" << endl;
//    cout << getPrintableVectorVectorString(unitlist) << endl;
//    cout << "end unit list" << endl << endl;
	// make unit list dictionary - all units that contain the square
	for (string sq : squares) {
		vector<vector<string> > tempUnitList;
		tempUnitList.clear();
		for (vector<string> ul : unitlist) {
			for (string l : ul) {
				if (l == sq) {
					tempUnitList.push_back(ul);
				}
			}
		}
		units[sq] = tempUnitList;
	}
//    cout << "units" << endl;
//    for (string s : squares) {
//        cout << "Units " << s << endl;
//        cout << getPrintableVectorVectorString(units[s]) << endl ;
//    }
//    cout << "end units " << endl << endl;
	// make peer dictionary
	for (string s : squares) {
		set<string> vec; // use a set so there are no duplicates
		for (vector<string> u : units[s]) {
			for (string l : u) {
				if (l != s) {
					vec.insert(l);
				}
			}
		}
		vector<string> v(vec.begin(), vec.end());
		peers[s] = v;
	}
//    cout << "peers" << endl;
//    for (string s : squares) {
//        cout << "Peers " << s << endl;
//        cout << getPrintableStringVector(peers[s]) << endl << endl;
//    }
//    cout << "end peers" << endl << endl;

    
    
	//ROWCOL rc;
	ROWCOL* rcp;
    uint32_t r,c;
    // squres
	for (r = 0; r < strlen(c_rows); r++) {
		for (c = 0; c < strlen(c_cols); c++) {
			rcp = Guess::textToRC(squares[c + r * 9].c_str());
			//c_squares[r][c] = *rcp;
			strncpy(sudoku[r][c].name, Guess::RCToText(*rcp), 3);
			// clear the puzzle while we are here
			sudoku[r][c].value = '.';
			strncpy(sudoku[r][c].allowableValues, c_digits, 10);
		}
	}
	// unitlists.  all rows, all cols, all little squares
    // unitlist is 27 x 9
    uint32_t ulIndex = 0;
    uint32_t ulEntry = 0;
    // first 9 colums
    for (c = 0 ; c < numCols ; c++) {
        for(r = 0 ; r < numRows ; r++) {
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++;
        }
        ulIndex++;
        ulEntry = 0;
    }
    // now 9 rows
    for (r = 0 ; r < numCols ; r++) {
        for( c = 0 ; c < numRows ; c++) {
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++;
        }
        ulIndex++;
        ulEntry = 0;
    }
    // 3x3 squares
    for(r=0;r<3;r++ ) { for (c=0;c<3;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=3;r<6;r++ ) { for (c=0;c<3;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=6;r<9;r++ ) { for (c=0;c<3;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=0;r<3;r++ ) { for (c=3;c<6;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=3;r<6;r++ ) { for (c=3;c<6;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=6;r<9;r++ ) { for (c=3;c<6;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=0;r<3;r++ ) { for (c=6;c<9;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=3;r<6;r++ ) { for (c=6;c<9;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }
    ulIndex++;
    ulEntry = 0;
    for(r=6;r<9;r++ ) { for (c=6;c<9;c++){
            c_unitList[ulIndex][ulEntry].row = r;
            c_unitList[ulIndex][ulEntry].col = c;
            ulEntry++; } }

//	for (int ul = 0; ul < dimNumUnitLists; ul++) {
//		for (int i = 0; i < dimNumSquaresPerUnit;i++) {
//			rcp = Guess::textToRC(unitlist[ul][i].c_str());
//			c_unitList[ul][i] = *rcp;
//		}
//	}
    
	// units
    int unitNumber = 0 ;
	for (r = 0; r < numRows ; r++) {
		for (c = 0; c < numCols ; c++) {
            unitNumber = 0;
			for ( int nu = 0; nu < dimNumUnitLists ; nu++) {
                for( int u = 0 ; u < dimNumElementsInUnitList ; u++) {
                    if (c_unitList[nu][u].row == r && c_unitList[nu][u].col == c) {
                        memcpy(&sudoku[r][c].units[unitNumber],&c_unitList[nu],sizeof(ROWCOL) * dimNumElementsInUnitList);
                        unitNumber++;
                        continue;
                    }
				}
			}
		}
	}
	// peers
    // peers
    ROWCOL rrcc;
    for (int r = 0; r < numRows; r++) {
        rrcc.row = r;
        for (int c = 0; c < numCols; c++) {
            rrcc.col = c;
            for (int np = 0; np < dimNumPeers; np++) {
                rcp = Guess::textToRC(peers[Guess::RCToText(rrcc)][np].c_str());
                //c_peers[r][c][np] = rc;
                sudoku[r][c].peers[np] = *rcp;
            }
        }
    }
    
    //    int peerNumber = 0;
//	for (int r = 0; r < numRows; r++) {
//		for (int c = 0; c < numCols; c++) {
//            // look through each unit and see if it has this square in it.  if it does, copy every element that is NOT this square to peers
//            peerNumber = 0;
//            for (int nu = 0 ; nu < dimNumUnitLists ; nu++) {
//                for (int u = 0 ; u < dimNumElementsInUnitList ; u++) {
//                    if(c_unitList[nu][u].row == r && c_unitList[nu][u].col == c) {
//                        printf("u");
//                        /// c_unitList[nu] as this square in it, now just copy the elements that do not equal this square
//                        for(int uu = 0 ; uu < dimNumElementsInUnitList ; uu++) {
//                            if(!(c_unitList[nu][uu].row == r && c_unitList[nu][uu].col == c)) {
//                                // make sure it is not already in the set of peers
//                                for(int p = 0 ; p < peerNumber+1 ; p++) {
//                                    if(!(sudoku[r][c].peers[p].row == c_unitList[nu][uu].row && sudoku[r][c].peers[p].col == c_unitList[nu][uu].col)) {
//                                        printf("c");
//                                        sudoku[r][c].peers[peerNumber].row = c_unitList[nu][uu].row;
//                                        sudoku[r][c].peers[peerNumber].col = c_unitList[nu][uu].col;
//                                        peerNumber++;
//                                        break;
//                                    } else {
//                                        printf("z");
//                                    }
//                                }
//                            } else {
//                                printf("x");
//                            }
//
//                        }
//                        printf("\n");
//                    }
//                    
//                }
//            }
//            printf("Number of peers found was %d\n",peerNumber);
//            printf("%d%d\n",r,c);
//            for(int i = 0 ; i < peerNumber ; i++) {
//                printf("%d%d ",sudoku[r][c].peers[peerNumber].row,sudoku[r][c].peers[peerNumber].col);
//            }
//            printf("\n\n");
//		}
//	}
	int jj = 0;
    jj=1;
    printSudoku();
}

void Sudoku::clearPuzzle(void) {
	for( int r = 0 ; r < 9 ; r++) {
		for (int c = 0; c < 9; c++) {
			sudoku[r][c].value ='.';
			strncpy(sudoku[r][c].allowableValues, "123456789", 10);
		}
	}
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


bool Sudoku::setPuzzle(const char* p) {
	if (strlen(p) != 81)
		return false;
	clearPuzzle();
	for (int32_t r = 0; r < numRows; r++) {
		for (int32_t c = 0;c < numCols; c++) {
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

void Sudoku::printPuzzle(sudokuType state) {
	char header[] =  "     1   2   3    4   5   6    7   8   9";
		char top[] = "  =========================================";
	char row_sep[] = "  || --------- || --------- || --------- ||";
	char col_sep[] = "||";
	char num_sep[] = "|";
	cout << endl << header << endl;
	cout << top << endl;
	for (uint32_t r = 0; r < numRows; r++) {
		cout << c_rows[r] << " " << col_sep;
		for (uint32_t c = 0; c < numCols; c++) {
			if (state[r][c].value == '0') {
				cout << "  ";
			}
			else {
				cout << " " << state[r][c].value;
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

void Sudoku::printPuzzle(void) {
	printPuzzle(sudoku);
}

void Sudoku::printAllowableValues(sudokuType state) {
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
		cout << c_rows[r] << " " << col_sep;
		//cout << r << " " << col_sep;
		for (uint32_t c = 0; c < numCols; c++) {
			if (state[r][c].value == '0') {
				cout << "  ";
			}
			else {
				cout << " " << setw(9) << state[r][c].allowableValues;
			}
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

void Sudoku::printAllowableValues(void) {
	printAllowableValues(sudoku);

}

void Sudoku::printAllowableValues(char* title) {
    printf("%s",title);
	printAllowableValues();
}

/**********************************************************
**********   Solving Functions ***************************
***********************************************************/
//bool Sudoku::setValue(string square, string value) {
//	return true;
//}

uint32_t Sudoku::countOccurrences(char* str, char ch) {
	uint32_t count = 0;
	uint32_t i = 0;
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

bool Sudoku::setValue(uint32_t r, uint32_t c, char value) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
	if (strchr(sudoku[r][c].allowableValues,value) == NULL)
		return false;
	if (value == '0' || value == '.') {
		strncpy(sudoku[r][c].allowableValues, c_digits, 10);
	}
	else {
		strncpy(sudoku[r][c].allowableValues, "", 2);
	}
	sudoku[r][c].value = value;
	ROWCOL rc;
	for (uint32_t p = 0; p < dimNumPeers; p++) {
		rc = sudoku[r][c].peers[p];
		removeChar(sudoku[rc.row][rc.col].allowableValues, value);
	}
	int j = 12;
	j = 13;
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
//	char tempstr[200];
	bool solvedSome = true; // set to true to ensure one iteration
	while (solvedSome == true) {
        solvedSome = false; // set to false to exit after one interation if nothing is set
        // find squares with only one available value
        for (uint32_t r = 0; r < numRows; r++) {
            for (uint32_t c = 0; c < numCols; c++) {
                if (strlen(sudoku[r][c].allowableValues) == 1) {
                    setValue(r, c, (char)sudoku[r][c].allowableValues[0]);
                    solvedSome = true;
                }
            }
        }
        // look through all units and see if any value appears only one time
        char allValues[9 * 82];
        for (uint32_t ul = 0; ul < dimNumUnitLists; ul++) {
            strncpy(allValues, "", 2);
            for (uint32_t s = 0; s < dimNumElementsInUnitList; s++) {
                ROWCOL rc = c_unitList[ul][s];
                strncat(allValues, sudoku[rc.row][rc.col].allowableValues, 10);
            }
            // count to see if any value only appears one time in a unit
            for (uint32_t d = 0; d < dimNumDigits;d++) {
                size_t c = countOccurrences(allValues, c_digits[d]);
                if (c == 1) {
                    for (uint32_t s = 0; s < dimNumElementsInUnitList; s++) {
                        ROWCOL rc = c_unitList[ul][s];
                        size_t c1 = countOccurrences(sudoku[rc.row][rc.col].allowableValues, c_digits[d]);
                        if (c1 == 1) {
                            setValue(rc.row, rc.col, c_digits[d]);
                            solvedSome = true;
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
	// a puzzle is solved if each unit in unitlist contains values of 1-9
	char unitValues[10];
	ROWCOL rc;
	// first check - get puzzle text and look for '.'
    for(uint32_t r = 0 ; r < numRows ; r++) {
        for (uint32_t c = 0 ; c < numCols ; c++) {
            if(sudoku[r][c].value == '.')
                return false;
        }
    }
	for (uint32_t ul = 0; ul < dimNumUnitLists;ul++) {
		for (uint32_t u = 0; u < dimNumElementsInUnitList; u++) {
			rc = c_unitList[ul][u];
			unitValues[u] = sudoku[rc.row][rc.col].value;
		}
		unitValues[9] = '\0';
		// string is built.  make sure each digit appears exactly once
		for (uint32_t d = 0; d < dimNumDigits; d++) {
			if (countOccurrences(unitValues, c_digits[d]) != 1) {
				return false;
			}
		}
	}
	return true;
}

//char* Sudoku::getPuzzleText(void) {
//	static char retval[valueStringLength];
//	memset((void*)retval, 0, 83);
//	for (uint32_t r = 0; r < numRows; r++) {
//		for (uint32_t c = 0; c < numCols; c++) {
//			retval[c + r * numCols] = sudoku[r][c].value;
//		}
//	}
//	return retval;
//}

bool Sudoku::removeAllowableValue(uint8_t r, uint8_t c, char value) {
    bool retval;
    char* pstr = sudoku[r][c].allowableValues;
    if(countOccurrences(pstr,value) == 0) {
        retval = false;
    } else {
        removeChar(pstr,value);
        retval = true;
    }
    return retval;
}

bool Sudoku::removeAllowableValue(ROWCOL rc, char value) {
    return removeAllowableValue(rc.row, rc.col, value);
}

bool Sudoku::removeAllowableValue(Guess g) {
    return removeAllowableValue(g.rc.row, g.rc.col, g.guess);
}
bool Sudoku::guessesRemain(void) {
	for (uint32_t r = 0; r < numRows; r++) {
		for (uint32_t c = 0; c < numCols; c++) {
			if (strlen(sudoku[r][c].allowableValues) > 0)
				return true;
		}
	}
	return false;
}

Guess Sudoku::getGuess() { // returns square, value
	size_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;
    ROWCOL rc[81];
    uint32_t numFound = 0;
    // search through all squares and find minimum number of availableValues
    for(uint32_t r = 0 ; r < numRows ; r++) {
        for (uint32_t c = 0 ; c < numCols ; c++) {
            len = strlen(sudoku[r][c].allowableValues);
            if(len != 0) {
                minCount = min(minCount, len);
            }
        }
    }
    // make a list of all squares with the mininum values
    for(uint32_t r = 0 ; r < numRows ; r++) {
        for (uint32_t c = 0 ; c < numCols ; c++) {
            len = strlen(sudoku[r][c].allowableValues);
            if(len == minCount) {
                rc[numFound].row = r;
                rc[numFound].col = c;
                numFound++;
            }
        }
    }
    // pick one
    ROWCOL rcg = rc[rand() % numFound];
    // now pick random number
    char* pstr = sudoku[rcg.row][rcg.col].allowableValues;
    char g = pstr[rand() % strlen(pstr)];
    newGuess = Guess(sudoku,rcg,g);
    return newGuess;
}

bool Sudoku::popGuess() {
    if(currentGuess == 0)
        return false;
    Guess lastGuess = guessStack[currentGuess-1];
    memcpy(sudoku, lastGuess.state, sizeof (sudokuType));
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
        for (uint32_t g = 0 ; g < currentGuess ; g++) {
            printf("%s <- %c ",Guess::RCToText(guessStack[g].rc), guessStack[g].guess);
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
bool Sudoku::setValue(ROWCOL rc, char value) {
    return setValue(rc.row, rc.col,value);
}

bool Sudoku::setValue(Guess g) {
    return setValue(g.rc.row, g.rc.col, g.guess);
    
}
bool Sudoku::startGuessing() {
    currentGuess = 0;
    while(!isPuzzleSolved()) {
        while(guessesRemain()) {
            Guess g = getGuess();
            pushGuess(g);
            setValue(g);
            solveOnes();
            if ( !isPuzzleSolved() && !guessesRemain()) {
                popGuess();
            }
        }
        if( !isPuzzleSolved()) {
            if (popGuess() == false)
                return false;
        }
    }
    return isPuzzleSolved();
}

 
 void Sudoku::printSudoku() {
	 printSudoku(sudoku);
 }

 void Sudoku::printSudoku(sudokuType s) {
	 for (int32_t r = 0; r < numRows; r++) {
		 for (int32_t c = 0; c < numCols; c++) {
			 printf("Row: %d, Column: %d\n", r, c);
			 printf("\tName: %s\n", sudoku[r][c].name);
			 printf("\tValue: %c\n", sudoku[r][c].value);
			 printf("\tAllowable: %s\n", sudoku[r][c].allowableValues);
			 printf("\tUnits\n");
			 for (uint32_t nu = 0; nu < dimNumUnits; nu++) {
				 printf("\t\t");
				 for (uint32_t ns = 0; ns < dimNumSquaresPerUnit; ns++) {
					 printf("%s ", Guess::RCToText(sudoku[r][c].units[nu][ns]));
				 }
				 printf("\n");
			 }
			 printf("\tPeers\n");
			 printf("\t\t");
			 for (uint32_t p = 0; p < dimNumPeers; p++) {
				 printf("%s ", Guess::RCToText(sudoku[r][c].peers[p]));
			 }
			 printf("\n\n");
		 }
	 }
	 printf("Size of sudoku is %d\n", (int32_t)sizeof(sudokuType));
 }

 char* testStr(ROWCOL rc) {
	 static char text[3];
	 text[0] = (char)('A' + rc.row);
	 text[1] = (char)('1' + rc.col);
	 text[2] = '\0';
	 return text;
 }

void Sudoku::test(void) {


}
