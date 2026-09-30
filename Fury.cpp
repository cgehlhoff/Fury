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
    MoveInfo info;
    
    info = b.makeMove(E2, E4, PAWN, WHITE);

    printBitboard(b.allPieces());
    std::cout << "\n\n\n";

    b.unmakeMove(E2, E4, PAWN, WHITE, info);

    printBitboard(b.allPieces());

    return 0;
}