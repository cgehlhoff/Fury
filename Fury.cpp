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

int main() {

    Board b;

    std::string testFEN = "6k1/5ppp/8/8/8/8/8/R5K1 w - - 0 1";
    Color side = parseFEN(testFEN, b);

    std::optional<Move> result = findBestMove(2, side, b);

    if (result.has_value()) {
        Move m = result.value();
        std::cout << char('a' + m.from % 8) << char('1' + m.from / 8)
            << char('a' + m.to % 8) << char('1' + m.to / 8) << "\n";
    }

    return 0;
}