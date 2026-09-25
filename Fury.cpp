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

    // --- Test 1: non-capture move (white knight b1 -> a3, empty square) ---
    uint64_t before = b.pieces[WHITE][KNIGHT];
    std::cout << "Before move:\n";
    printBitboard(before);

    MoveInfo info1 = b.makeMove(B1, A3, KNIGHT, WHITE);
    std::cout << "After makeMove:\n";
    printBitboard(b.pieces[WHITE][KNIGHT]);

    b.unmakeMove(B1, A3, KNIGHT, WHITE, info1);
    std::cout << "After unmakeMove:\n";
    printBitboard(b.pieces[WHITE][KNIGHT]);

    if (b.pieces[WHITE][KNIGHT] == before)
        std::cout << "TEST 1 PASSED - knight bitboard restored\n";
    else
        std::cout << "TEST 1 FAILED\n";

    // --- Test 2: manufactured capture (force a black pawn onto a3, then capture it) ---
    b.pieces[BLACK][PAWN] |= (1ULL << A3); // manually place a black pawn on a3 for testing

    uint64_t whiteBefore = b.pieces[WHITE][KNIGHT];
    uint64_t blackBefore = b.pieces[BLACK][PAWN];

    MoveInfo info2 = b.makeMove(B1, A3, KNIGHT, WHITE);
    std::cout << "wasCapture: " << info2.wasCapture << "\n";

    b.unmakeMove(B1, A3, KNIGHT, WHITE, info2);

    if (b.pieces[WHITE][KNIGHT] == whiteBefore && b.pieces[BLACK][PAWN] == blackBefore)
        std::cout << "TEST 2 PASSED - both bitboards restored after capture undo\n";
    else
        std::cout << "TEST 2 FAILED\n";

    return 0;
}