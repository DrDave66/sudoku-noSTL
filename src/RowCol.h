//
//  RowCol.hpp
//  sudoku
//
//  Created by Dave Landis on 11/20/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//

#ifndef _ROWCOL_H
#define _ROWCOL_H

#include <stdint.h>
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdlib>


class RowCol {
public:
    RowCol();
    RowCol(const RowCol&);
    RowCol(const uint8_t r, const uint8_t c);
    RowCol& operator=(const RowCol& cpy);
    bool operator==(const RowCol& rc);
    
    char* toText();
    static void printArray(RowCol*, uint8_t num);
    static char* toText(RowCol&);
    static char* toText(const uint8_t r, const uint8_t c);
    static RowCol& fromText(const char* text);
    char row;
    char col;
private:
    static char str[3];
};

#endif /* RowCol_hpp */
