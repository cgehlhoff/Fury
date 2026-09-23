#pragma once
#include <cstdint>
#include "types.h"

struct Board {
    uint64_t pieces[NUM_COLORS][NUM_PIECE_TYPES];

    Board();
};

void printBitboard(uint64_t board);