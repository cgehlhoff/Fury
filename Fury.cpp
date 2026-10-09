// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"
#include "fen.h"
#include "search.h"
#include "uci.h"

int main() {
    uciLoop();
    return 0;
}