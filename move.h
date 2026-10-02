#pragma once
#include "types.h"
#include <optional>

struct MoveInfo {
    Piece capturedPiece = PAWN;
    bool wasCapture = false;
    bool wasEnPassant = false;
    std::optional<int> previousEnPassantTarget;
    bool previousWhiteCanCastleKingside; // also can go down to 4 bit
    bool previousWhiteCanCastleQueenside;
    bool previousBlackCanCastleKingside;
    bool previousBlackCanCastleQueenside;
};

struct Move {
    int from;
    int to;
    Piece piece;
};