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
    
    uint64_t result = perft(4, WHITE, b);
    std::cout << result;
    

    return 0;
}