#include <cstdint>
#include <vector>
#include "types.h"
#include "board.h"
#include "attacks.h"

uint64_t getKnightMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getKnightAttacks(square) & (~b.piecesOf(color));
	return boardToReturn;

}

uint64_t getKingMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getKingAttacks(square) & (~b.piecesOf(color));
	return boardToReturn;

}

uint64_t getRookMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getRookAttacks(square, b.allPieces()) & (~b.piecesOf(color));
	return boardToReturn;

}

uint64_t getBishopMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getBishopAttacks(square, b.allPieces()) & (~b.piecesOf(color));
	return boardToReturn;

}

uint64_t getQueenMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getQueenAttacks(square, b.allPieces()) & (~b.piecesOf(color));
	return boardToReturn;

}

uint64_t getPawnPushes(int square, Color color, const Board& b) {

    uint64_t boardToReturn = 0ULL;
    int file = square % 8;
    int rank = square / 8;
    int rankDelta = (color == WHITE) ? 1 : -1;
    int startRank = (color == WHITE) ? 1 : 6;

    int singleRank = rank + rankDelta;
    int singleSquare = 8 * singleRank + file;

    // single push
    if (!(b.allPieces() & (1ULL << singleSquare))) {
        boardToReturn |= (1ULL << singleSquare);

        // double push
        if (rank == startRank) {
            int doubleRank = rank + (2 * rankDelta);
            int doubleSquare = 8 * doubleRank + file;
            if (!(b.allPieces() & (1ULL << doubleSquare))) {
                boardToReturn |= (1ULL << doubleSquare);
            }
        }
    }

    return boardToReturn;
}

uint64_t getPawnMoves(int square, Color color, const Board& b) {

    uint64_t boardToReturn = 0ULL;
    Color enemyColor = (color == WHITE) ? BLACK : WHITE;

    boardToReturn |= getPawnPushes(square, color, b);
    boardToReturn |= getPawnAttacks(square, color) & b.piecesOf(enemyColor);
    
    return boardToReturn;

}

bool isSquareAttacked(int square, Color attackingColor, const Board& b) {

    if ((getKnightAttacks(square) & b.pieces[attackingColor][KNIGHT]) != 0ULL) return true;
    if ((getBishopAttacks(square, b.allPieces()) & b.pieces[attackingColor][BISHOP]) != 0ULL) return true;
    if ((getRookAttacks(square, b.allPieces()) & b.pieces[attackingColor][ROOK]) != 0ULL) return true;
    if ((getQueenAttacks(square, b.allPieces()) & b.pieces[attackingColor][QUEEN]) != 0ULL) return true;
    if ((getKingAttacks(square) & b.pieces[attackingColor][KING]) != 0ULL) return true;
    Color defenderColor = (attackingColor == WHITE) ? BLACK : WHITE;
    if ((getPawnAttacks(square, defenderColor) & b.pieces[attackingColor][PAWN]) != 0ULL) return true;

    return false;
}

// filters out moves that would leave king in check
uint64_t filterLegalMoves(int from, Piece piece, Color color, uint64_t pseudoMoves, Board& b) {

    uint64_t legalMoves = 0ULL;
    Color enemyColor = (color == WHITE) ? BLACK : WHITE;
    int to = 0;
    MoveInfo info;

    while (pseudoMoves != 0ULL) {

        to = bitscan(pseudoMoves);
        pseudoMoves &= pseudoMoves - 1;

        info = b.makeMove(from, to, piece, color);

        if (!isSquareAttacked(bitscan(b.pieces[color][KING]), enemyColor, b)) {
            legalMoves |= (1ULL << to);
        }
        
        b.unmakeMove(from, to, piece, color, info);
        
    }

    return legalMoves;
}


// for each piece type (PAWN through KING):
//     for each piece of that type belonging to `color`:
//         from = bitscan that piece's bit, clear it, advance
//         pseudoMoves = call the matching getXMoves(from, color, b)
//         legalMoves = filterLegalMoves(from, pieceType, color, pseudoMoves, b)
//         for each set bit in legalMoves:
//             build a Move{from, to, pieceType} and push_back it

std::vector<Move> generateAllMoves(Color color, Board& b) {
    std::vector<Move> moves;
    uint64_t pieceBitboard = 0ULL;
    uint64_t pseudoMoves = 0ULL;
    uint64_t legalMoves = 0ULL;
    int from = 0;
    int to = 0;

    for (int pieceType = 0; pieceType < NUM_PIECE_TYPES; pieceType++) {
        pieceBitboard = b.pieces[color][pieceType];

        while (pieceBitboard != 0ULL) {
            from = bitscan(pieceBitboard);
            pieceBitboard &= pieceBitboard - 1;

            switch (pieceType) {
                case PAWN:
                    pseudoMoves = getPawnMoves(from, color, b);
                    break;
                case KNIGHT:
                    pseudoMoves = getKnightMoves(from, color, b);
                    break;
                case BISHOP:
                    pseudoMoves = getBishopMoves(from, color, b);
                    break;
                case ROOK:
                    pseudoMoves = getRookMoves(from, color, b);
                    break;
                case QUEEN:
                    pseudoMoves = getQueenMoves(from, color, b);
                    break;
                case KING:
                    pseudoMoves = getKingMoves(from, color, b);
                    break;
            }

            legalMoves = filterLegalMoves(from, (Piece)pieceType, color, pseudoMoves, b);
            
            while (legalMoves != 0ULL) {
                to = bitscan(legalMoves);
                legalMoves &= legalMoves - 1;

                Move m;
                m.from = from;
                m.to = to;
                m.piece = (Piece)pieceType;
                moves.push_back(m);
            }
        }
    }

    return moves;
}