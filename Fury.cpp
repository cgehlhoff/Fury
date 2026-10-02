// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"
#include "fen.h"

int main() {
    Board b;

    Color side = parseFEN("rnbqkbnr/pp2pp1p/2pp4/5Pp1/8/4P3/PPPP2PP/RNBQKBNR w KQkq g6 0 4", b);

    printBitboard(b.pieces[WHITE][PAWN]);
    printBitboard(b.pieces[BLACK][PAWN]);
    std::cout << "side to move: " << (side == WHITE ? "WHITE" : "BLACK") << "\n";
    std::cout << "en passant target: " << (b.enPassantTarget.has_value() ? b.enPassantTarget.value() : -1) << "\n";
    std::cout << "white KQ: " << b.whiteCanCastleKingside << " " << b.whiteCanCastleQueenside << "\n";
    std::cout << "black kq: " << b.blackCanCastleKingside << " " << b.blackCanCastleQueenside << "\n";

    /*for (int d = 1; d <= 6; d++) {
        std::cout << "perft(" << d << ") = " << perft(d, WHITE, b) << "\n";
    }*/

    return 0;
}