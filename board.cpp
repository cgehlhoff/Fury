#include "board.h"
#include "types.h"
#include "move.h"
#include <iostream>
#include <optional>

Board::Board() {

    pieces[WHITE][PAWN] = 0x000000000000FF00ULL;
    pieces[WHITE][KNIGHT] = 0x0000000000000042ULL;
    pieces[WHITE][BISHOP] = 0x0000000000000024ULL;
    pieces[WHITE][ROOK] = 0x0000000000000081ULL;
    pieces[WHITE][QUEEN] = 0x00000000000008ULL;
    pieces[WHITE][KING] = 0x00000000000010ULL;

    pieces[BLACK][PAWN] = 0x00FF000000000000ULL;
    pieces[BLACK][KNIGHT] = 0x4200000000000000ULL;
    pieces[BLACK][BISHOP] = 0x2400000000000000ULL;
    pieces[BLACK][ROOK] = 0x8100000000000000ULL;
    pieces[BLACK][QUEEN] = 0x0800000000000000ULL;
    pieces[BLACK][KING] = 0x1000000000000000ULL;

}

uint64_t Board::allPieces() const {
    uint64_t boardToReturn = 0ULL;

    for (int i = 0; i < NUM_COLORS; i++) {
        for (int j = 0; j < NUM_PIECE_TYPES; j++) {
            boardToReturn |= pieces[i][j];
        }
    }

    return boardToReturn;

}

uint64_t Board::piecesOf(Color color) const {
    uint64_t boardToReturn = 0ULL;

    for (int j = 0; j < NUM_PIECE_TYPES; j++) {
        boardToReturn |= pieces[color][j];
    }

    return boardToReturn;
}

void printBitboard(uint64_t board) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            std::cout << ((board & (1ULL << square)) ? '1' : '0') << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

MoveInfo Board::makeMove(int from, int to, Piece piece, Color color) {
    MoveInfo info;
    info.wasCapture = false;
    info.wasEnPassant = false;

    info.previousEnPassantTarget = enPassantTarget;
    info.previousWhiteCanCastleKingside = whiteCanCastleKingside;
    info.previousWhiteCanCastleQueenside = whiteCanCastleQueenside;
    info.previousBlackCanCastleKingside = blackCanCastleKingside;
    info.previousBlackCanCastleQueenside = blackCanCastleQueenside;

    if (piece == PAWN && std::abs(to - from) == 16) {
        enPassantTarget = (from + to) / 2;
    }
    else {
        enPassantTarget = std::nullopt;
    }

    // maybe optimize this later with bits and less ifs
    if (piece == ROOK && color == WHITE && from == A1) whiteCanCastleQueenside = false;
    if (piece == ROOK && color == WHITE && from == H1) whiteCanCastleKingside = false;
    if (piece == ROOK && color == BLACK && from == A8) blackCanCastleQueenside = false;
    if (piece == ROOK && color == BLACK && from == H8) blackCanCastleKingside = false;
    if (to == A1) whiteCanCastleQueenside = false;
    if (to == H1) whiteCanCastleKingside = false;
    if (to == A8) blackCanCastleQueenside = false;
    if (to == H8) blackCanCastleKingside = false;

    if (piece == KING && color == WHITE) {
        whiteCanCastleKingside = false;
        whiteCanCastleQueenside = false;
    }
    if (piece == KING && color == BLACK) {
        blackCanCastleKingside = false;
        blackCanCastleQueenside = false;
    }

    Color enemyColor = (color == WHITE) ? BLACK : WHITE;

    if (piece == PAWN && info.previousEnPassantTarget.has_value() && to == info.previousEnPassantTarget.value()) {
        // en  passant capture
        int capturedSquare = (color == WHITE) ? to - 8 : to + 8;
        info.wasCapture = true;
        info.wasEnPassant = true;
        info.capturedPiece = PAWN;
        pieces[enemyColor][PAWN] &= (~(1ULL << capturedSquare));
    }
    else if (piece == KING && std::abs(to - from) == 2) {
        bool kingside = (to > from);
        int rookFrom, rookTo;

        if (color == WHITE) {
            rookFrom = kingside ? H1 : A1;   // rook's home square
            rookTo = kingside ? F1 : D1;   // square the rook jumps to
        }
        else {
            rookFrom = kingside ? H8 : A8;
            rookTo = kingside ? F8 : D8;
        }

        pieces[color][ROOK] &= (~(1ULL << rookFrom));  // rook leaves home
        pieces[color][ROOK] |= (1ULL << rookTo);        // rook lands on the crossed square
    }
    else if (piecesOf(enemyColor) & (1ULL << to)) {
        for (int i = 0; i < NUM_PIECE_TYPES; i++) {
            if (pieces[enemyColor][i] & (1ULL << to)) {
                info.wasCapture = true;
                info.capturedPiece = (Piece)i;
                pieces[enemyColor][i] &= (~(1ULL << to));
                break;
            }
        }
    }

    pieces[color][piece] &= (~(1ULL << from));
    pieces[color][piece] |= (1ULL << to);

    return info;

}

void Board::unmakeMove(int from, int to, Piece piece, Color color, MoveInfo info) {
    pieces[color][piece] &= (~(1ULL << to));
    pieces[color][piece] |= (1ULL << from);
    Color enemyColor = (color == WHITE) ? BLACK : WHITE;

    if (info.wasCapture) {
        if (info.wasEnPassant) {
            int capturedSqaure = (color == WHITE) ? to - 8 : to + 8;
            pieces[enemyColor][PAWN] |= (1ULL << capturedSqaure);
        }
        else {
            pieces[enemyColor][info.capturedPiece] |= (1ULL << to);
        }
    }

    if (piece == KING && std::abs(to - from) == 2) {
        bool kingside = (to > from);
        int rookFrom, rookTo;

        if (color == WHITE) {
            rookFrom = kingside ? H1 : A1;
            rookTo = kingside ? F1 : D1;
        }
        else {
            rookFrom = kingside ? H8 : A8;
            rookTo = kingside ? F8 : D8;
        }

        pieces[color][ROOK] &= (~(1ULL << rookTo));
        pieces[color][ROOK] |= (1ULL << rookFrom);
    }

    enPassantTarget = info.previousEnPassantTarget;

    whiteCanCastleKingside = info.previousWhiteCanCastleKingside;
    whiteCanCastleQueenside = info.previousWhiteCanCastleQueenside;
    blackCanCastleKingside = info.previousBlackCanCastleKingside;
    blackCanCastleQueenside = info.previousBlackCanCastleQueenside;
}