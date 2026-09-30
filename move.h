#pragma once
#include "types.h"

struct MoveInfo {
    Piece capturedPiece;
    bool wasCapture;
};

struct Move {
    int from;
    int to;
    Piece piece;
};