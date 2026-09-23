// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "types.h"
#include "attacks.h"


int main()
{
    Board b;
    printBitboard(b.pieces[WHITE][PAWN]);

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getKnightAttacks(A1));

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getKingAttacks(E4));

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getPawnAttacks(E4, BLACK));

    return 0;
}