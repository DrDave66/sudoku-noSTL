//
//  RowCol.cpp
//  sudoku
//
//  Created by Dave Landis on 11/20/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//
#include <string>

using namespace std;

#include "RowCol.h"

RowCol::RowCol() {
    row = 99;
    col = 90;
}

RowCol::RowCol(const RowCol& rc) {
    row = rc.row;
    col = rc.col;
}
RowCol::RowCol(const uint8_t r, const uint8_t c) {
    row = r;
    col = c;
}
RowCol& RowCol::operator=(const RowCol& cpy) {
    row = cpy.row;
    col = cpy.col;
    return *this;
}

bool RowCol::operator==(const RowCol& rc){
    if(row == rc.row && col == rc.col){
        return true;
    }
    else
        return false;
}
RowCol& RowCol::fromText(const char* text) {
    static RowCol rc;
    rc.row = (char)(text[0] - 'A');
    rc.col = (char)atoi(&text[1]) - 1;
    return rc;
}

char* RowCol::toText() {
    static char text[3];
    text[0] = (char)('A' + row);
    text[1] = (char)('1' + col);
    text[2] = '\0';
    return text;
}

char* RowCol::toText(const uint8_t r, const uint8_t c) {
    static char text[3];
    text[0] = (char)('A' + r);
    text[1] = (char)('1' + c);
    text[2] = '\0';
    return text;
}

char* RowCol::toText(RowCol& rc) {
    static char text[3];
    text[0] = (char)('A' + rc.row);
    text[1] = (char)('1' + rc.col);
    text[2] = '\0';
    return text;
}

void RowCol::printArray(RowCol* rcp, uint8_t num) {
    string retval;
    for(uint8_t i = 0 ; i < num ; i++) {
        retval += toText(rcp[i]);
        retval += " ";
    }
    cout << retval << endl;
}




