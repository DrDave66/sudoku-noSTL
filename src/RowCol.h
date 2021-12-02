//
//  RowCol.hpp
//  sudoku3
//
//  Created by Dave Landis on 11/28/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//
#pragma once
#ifndef _ROWCOL
#define _ROWCOL

#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

class RowCol {
public:
    RowCol() {};
    RowCol(uint8_t r, uint8_t);
    RowCol(const RowCol&);

    RowCol& operator=(const RowCol cpy);
    void set(uint8_t r, uint8_t c);
    char* toString();
    void fromString(string rc);
    
    friend ostream& operator<< (ostream& stream, const RowCol&);
    
public:
	uint8_t row;
	uint8_t col;
};
inline bool operator == (const RowCol& lhs, const RowCol& rhs) { return (lhs.row == rhs.row && lhs.col == rhs.col);}
inline bool operator != (const RowCol& lhs, const RowCol& rhs) { return !(lhs == rhs);}
inline bool operator < (const RowCol& lhs,const RowCol& rhs) {if (lhs.row == rhs.row) return lhs.col < rhs.col; else return lhs.row < rhs.row;}
inline bool operator > (const RowCol& lhs,const RowCol& rhs) { return rhs < lhs;}
inline bool operator <= (const RowCol& lhs,const RowCol& rhs) { return !(lhs > rhs);}
inline bool operator >= (const RowCol& lhs,const RowCol& rhs) { return !(lhs < rhs);}
#endif /* _ROWCOL */
