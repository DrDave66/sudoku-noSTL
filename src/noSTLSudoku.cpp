// vcSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <ctime>
using namespace std;

#include "Puzzles.h"
#include "Sudoku.h"
#include "Guess.h"
#include "PrecisionTimeLapse.h"
// solved with ones/peers
char grid1[] = "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3.."; // solves
char grid3[] = "8.2.5.7.1..7.8246..1.9.....6....18325.......91843....6.....4.2..9561.3..3.8.9.6.7";
// not solved with ones/peers
char easy505[] = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6";
char grid2[] =   "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
char hard1[] =   ".....6....59.....82....8....45........3........6..3.54...325..6..................";
char easy506[] = ".43.8.25.6.............1.949....4.7....6.8....1.2....382.5.............5.34.9.71.";
char easy501[] = "2...8.3...6..7..84.3.5..2.9...1.54.8.........4.27.6...3.1..7.4.72..4..6...4.1...3";
char easy502[] = "......9.7...42.18....7.5.261..9.4....5.....4....5.7..992.1.8....34.59...5.7......";
char TM392[] =   "1..65.8.2.3..2851458.314.97719.4.2..346275.8.8.5..3476.6.781945...569...9514.2768";
char TM604[] =   "2......9.3.49.1..2.95.6...3.6.459..8.8...6.1...28..4..7.13...86...172.49.296..7..";
char TM118[] =   "39...1487.173.4.598649.7...1..8.576...8436..1.4.71.8354.6.73.989..64837.7..5.9.4.";
char TM145[] =   "57.2.3..19.3..4.85.41...3..7.....19.....98...219..7.3..548.6.7...297..1..9..2..53";
char dummy[] =   "9..1.4..2.8..6..7..........4.......1.7.....3.3.......7..........3..7..8.1..2.9..4";
char diagonal[]= "...21......73......58......43.......2.......8.......76......25......73......98...";

void printPuzzleText(Sudoku ss) {
    for(int r = 0 ; r < 9 ; r++) {
        for (int c = 0 ; c < 9 ; c++) {
            cout << ss.puzzle[r][c];
        }
    }
    cout << endl;
}

#define SHORTMAIN

#ifdef SHORTMAIN
int main() {
    srand((unsigned int)time(NULL));
    Puzzles pp("../sudoku-puzzles/10000S.txt");
    Sudoku s(diagonal);
    s.solvePuzzle();
    printf("Solved = %d\n",s.isPuzzleSolved());
    int numPuzzles = pp.getNumberOfPuzzles();
    printf("%d puzzles read\n",numPuzzles);
    int numSolved = 0;
    int numFailed = 0;
    for (int i = 0 ; i < numPuzzles ; i++) {
        if(i % 10000 == 0) printf("%d\n",i);
        s.setPuzzle(pp.getPuzzle(i));
        if (s.isPuzzleSolved() == true)
            numSolved++;
        uint8_t r = rand() % 9;
        uint8_t c = rand() % 9;
        char value = s.puzzle[r][c];
        char newValue = rand() % 9 + '1';
        while(newValue == value) {
            newValue = rand() % 9 + '1';
        }
        s.puzzle[r][c] = newValue;
        if(s.isPuzzleSolved() == false)
            numFailed++;
    }
    printf("Number solved %d\n",numSolved);
    printf("Changes not solved %d\n",numFailed);
}
//int main() {
//    Sudoku s(easy505);
//    
//    s.printPuzzle();
//    s.printAllowableValues();
//    
//    cout << "Puzzle solved = " << s.isPuzzleSolved() << endl;
//    s.solvePuzzle();
//    cout << "Puzzle solved = " << s.isPuzzleSolved() << endl;
//    s.printPuzzle();
//    cout << "Puzzle solved = " << s.isPuzzleSolved() << endl;
//    printPuzzleText(s);
//    s.puzzle[0][0] = '3';
//    printPuzzleText(s);
//    cout << "Puzzle solved = " << s.isPuzzleSolved() << endl;
//    printf("\n");
//}

//int main() {
//	Puzzles p;
//	Sudoku s;
//	PrecisionTimeLapse ptl;
//	double minTime = 1000.0;
//	double maxTime = 0;
//	double time;
//	double sumTime = 0;
//	int i;
//	for (i = 0; i < 100; i++){
//		printf("Puzzle %d:", i);
//		p.generateRandomPuzzle(s,20);
//		//s.printPuzzle();
//		ptl.start();
//		bool solved = s.solvePuzzle();
//		ptl.stop();
//		//s.printPuzzle();
//		time = ptl.elapsed() * 1000;
//		minTime = min(minTime, time);
//		maxTime = max(maxTime, time);
//		sumTime += time;
//		printf(" solved %d, time: %f msec\n", solved, ptl.elapsed() * 1000);
//	}
//	printf("Min time: %0.4f msec: Max time: %0.4f, Average Time: %0.4f\n", minTime, maxTime, sumTime / (double)(i));
//}
//604
//118
//146

#else

int main()
{
	Puzzles p;
	Puzzles pf("../sudoku-puzzles/1MP.txt");
    //Puzzles pf("../../sudokus/SudokuPuzzles/10MPuzzles_Failed.txt");
	cout << pf.getNumberOfPuzzles() << " puzzles loaded" << endl;
	if (pf.getNumberOfPuzzles() == 0)
		return 1;
	Sudoku s;
	PrecisionTimeLapse total;
	PrecisionTimeLapse ptl;
	int solved = 0;
	double minTime = 100000.0;
	double maxTime = 0.0;
	double sumTime = 0.0;
	double time;
	total.start();
	for (uint32_t i = 0; i < pf.getNumberOfPuzzles(); i++) {

		s.setPuzzle(pf.getPuzzle(i));
		ptl.start();
		s.solvePuzzle();
		ptl.stop();
		if (s.isPuzzleSolved() == true)
		{
			solved += 1;
		}
		time = ptl.elapsed();

		minTime = min(minTime, time);
		maxTime = max(maxTime, time);
		sumTime += time;
        if((i+1) % 10000 == 0)
            printf("%d - solved %d, last time %f msec, average time %f msec\n",i+1,solved,time*1000.0,sumTime/i * 1000);
		//cout << time << " " << sumTime << "  ";
		//cout << "Total time: " << ptl.elapsedString() << " solved " << solved << " out of " << i+1 << endl;
		//cout << i << "\n";
	}
	total.stop();
    cout << "Solved " << solved << " out of " << pf.getNumberOfPuzzles() << endl;
	//cout << total.elapsed() << endl;
	cout << "Min time: " << minTime * 1000.0 << " ms, Max time: " << maxTime * 1000.0 << " ms, Average Time: " << (double)sumTime / (double)solved * 1000 << " ms, Total: " << total.elapsedString(SEC) << " sec" << endl;
}
#endif // SHORTMAIN
// removed solveones local vars     Min time: 0.024105 ms, Max time: 2.73368 ms, Average Time: 0.0337027 ms, Total: 6.149522 sec
// removed strchr in setvalue       Min time: 0.025124 ms, Max time: 5.33436 ms, Average Time: 0.0354065 ms, Total: 6.297419 sec
// removed redundant rc in setvalue Min time: 0.026409 ms, Max time: 6.66274 ms, Average Time: 0.0382568 ms, Total: 6.612621 sec
// after making RowCol a class      Min time: 0.02965 ms, Max time: 0.843668 ms, Average Time: 0.0406844 ms, Total: 7.088100 sec
//100k starting point               Min time: 0.023276 ms, Max time: 1.69528 ms, Average Time: 0.03387 ms, Total: 6.018346 sec
//100k improved STL                 Min time: 0.01634 ms, Max time: 13.2826 ms, Average Time: 0.0234467 ms, Total: 2.572433 sec
// 	    1   2   3    4   5   6    7   8   9
//   =========================================
// A || . | 4 | 3 || . | 8 | . || 2 | 5 | . ||
// B || 6 | . | . || . | . | . || . | . | . ||
// C || . | . | . || . | . | 1 || . | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | . | . || . | . | 4 || . | 7 | . ||
// E || . | . | . || 6 | . | 8 || . | . | . ||
// F || . | 1 | . || 2 | . | . || . | . | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | . || 5 | . | . || . | . | . ||
// H || . | . | . || . | . | . || . | . | 5 ||
// I || . | 3 | 4 || . | 9 | . || 7 | 1 | . ||
//   =========================================

//      1   2   3    4   5   6    7   8   9
//   =========================================
// A || 1 | 4 | 3 || 9 | 8 | 6 || 2 | 5 | 7 ||
// B || 6 | 7 | 9 || 4 | 2 | 5 || 3 | 8 | 1 ||
// C || 2 | 8 | 5 || 7 | 3 | 1 || 6 | 9 | 4 ||
//   || --------- || --------- || --------- ||
// D || 9 | 6 | 2 || 3 | 5 | 4 || 1 | 7 | 8 ||
// E || 3 | 5 | 7 || 6 | 1 | 8 || 9 | 4 | 2 ||
// F || 4 | 1 | 8 || 2 | 7 | 9 || 5 | 6 | 3 ||
//   || --------- || --------- || --------- ||
// G || 8 | 2 | 1 || 5 | 6 | 7 || 4 | 3 | 9 ||
// H || 7 | 9 | 6 || 1 | 4 | 3 || 8 | 2 | 5 ||
// I || 5 | 3 | 4 || 8 | 9 | 2 || 7 | 1 | 6 ||
//   =========================================
// Puzzle 6, Solved = True, Time = 0.2327 ms


// solved with ones/peers
// grid1 = '003020600900305001001806400008102900700000008006708200002609500800203009005010300'
// grid3 = "802050701007082460010900000600001832500000009184300006000004020095610300308090607"


// not solved with ones/peers
// easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6"
// grid2 = '4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......'
// hard1 = '.....6....59.....82....8....45........3........6..3.54...325..6..................'
