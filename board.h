#pragma once
#include <cstdint>

enum COLOR { WHITE, BLACK, NUM_COLORS };
enum PIECE { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NUM_PIECE_TYPES };

struct Board {
    uint64_t pieces[NUM_COLORS][NUM_PIECE_TYPES];

    Board();
};

void printBitboard(uint64_t board);