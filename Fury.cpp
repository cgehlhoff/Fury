// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"


int main()
{
    Board b;
    
    std::vector<Move> moves = generateAllMoves(WHITE, b);
    std::cout << moves.size();
    

    return 0;
}