//
//  RowCol.cpp
//  sudoku-STL
//
//  Created by Dave Landis on 11/28/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//
//#include <utility>
#include <iostream>

using namespace std;

#include "RowCol.h"

RowCol::RowCol(uint8_t r, uint8_t c) {
    row = r;
    col = c;
}

RowCol::RowCol(const RowCol& rc) {
    row = rc.row;
    col = rc.col;

}

RowCol& RowCol::operator=(RowCol cpy) {
    //swap(*this, cpy);  // trade our resources for cpy's
    row = cpy.row;
    col = cpy.col;
    return *this;    // our (old) resources get destroyed with cpyb
}

void RowCol::set(uint8_t r, uint8_t c) {
    row = r;
    col = c;
}

char* RowCol::toString() {
    static char retval[3];
    retval[0] = (char)('A' + row);
    retval[1] = (char)('1' + col);
    retval[2] = '\0';
    return retval;
}

void RowCol::fromString(string rc) {
    row = rc[0] - 'A';
    col = rc[1] - '1';
}
//inline int16_t RowCol::r() {return row;}
//inline int16_t RowCol::c() {return col;}

ostream& operator<< (ostream& os, const RowCol& rc) {
    RowCol rr(rc);
    os << rr.toString();
    return os;
}

