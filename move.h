#pragma once
#include "types.h"
#include <optional>

struct MoveInfo {
    Piece capturedPiece = PAWN;
    bool wasCapture = false;
    bool wasEnPassant = false;
    std::optional<int> previousEnPassantTarget;
};

struct Move {
    int from;
    int to;
    Piece piece;
};