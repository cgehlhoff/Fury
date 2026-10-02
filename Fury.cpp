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

int main() {

    Board b;

    std::cout << "PERFT DEPTH 6\n";
    for (int d = 1; d <= 6; d++) {
        std::cout << "perft(" << d << ") = " << perft(d, WHITE, b) << "\n";
    }

    std::string kiwipete = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    Color side = parseFEN(kiwipete, b);

    std::cout << "KIWIPETE DEPTH 4\n";

    for (int d = 1; d <= 4; d++) {
        std::cout << "perft(" << d << ") = " << perft(d, side, b) << "\n";
    } 

    return 0;
}