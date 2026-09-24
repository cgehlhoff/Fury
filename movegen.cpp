#include <cstdint>
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