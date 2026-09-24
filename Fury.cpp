// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"


int main()
{
    Board b;
    
    printBitboard(getPawnMoves(F6, WHITE, b));

    return 0;
}