#pragma once
#include <cstdint>
#include "types.h"

struct Board {
    uint64_t pieces[NUM_COLORS][NUM_PIECE_TYPES];

    Board();

    uint64_t piecesOf(Color color) const;
    uint64_t allPieces() const;
};

void printBitboard(uint64_t board);