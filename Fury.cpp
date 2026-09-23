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

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(b.allPieces());

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getRookAttacks(E4, 0ULL));

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getRookAttacks(E4, b.allPieces()));

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getBishopAttacks(E4, 0ULL));

    std::cout << "\n******\n******\n******\n\n";

    printBitboard(getQueenAttacks(E4, b.allPieces()));

    return 0;
}