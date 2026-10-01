#pragma once
#include <cstdint>
#include <optional>
#include "types.h"
#include "move.h"


struct Board {
    uint64_t pieces[NUM_COLORS][NUM_PIECE_TYPES];
    std::optional<int> enPassantTarget;

    Board();

    uint64_t piecesOf(Color color) const;
    uint64_t allPieces() const;
    MoveInfo makeMove(int from, int to, Piece piece, Color color);
    void unmakeMove(int from, int to, Piece piece, Color color, MoveInfo info);
};



void printBitboard(uint64_t board);