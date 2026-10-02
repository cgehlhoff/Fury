#pragma once
#include <cstdint>
#include <optional>
#include "types.h"
#include "move.h"


struct Board {
    uint64_t pieces[NUM_COLORS][NUM_PIECE_TYPES];
    std::optional<int> enPassantTarget;
    bool whiteCanCastleKingside; // this can be compacted to a 4 bit something later.
    bool whiteCanCastleQueenside;
    bool blackCanCastleKingside;
    bool blackCanCastleQueenside;

    Board();

    uint64_t piecesOf(Color color) const;
    uint64_t allPieces() const;
    MoveInfo makeMove(int from, int to, Piece piece, Color color, std::optional<Piece> promotionPiece = std::nullopt);
    void unmakeMove(int from, int to, Piece piece, Color color, MoveInfo info, std::optional<Piece> promotionPiece = std::nullopt);
};



void printBitboard(uint64_t board);