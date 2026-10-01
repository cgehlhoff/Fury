// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"


int main() {
    Board b;

    for (int d = 1; d <= 5; d++) {
        std::cout << "perft(" << d << ") = " << perft(d, WHITE, b) << "\n";
    }

    return 0;
}