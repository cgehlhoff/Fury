#include <cstdint>
#include "types.h"
#include "board.h"
#include "attacks.h"

uint64_t getKnightMoves(int square, Color color, const Board& b) {

	uint64_t boardToReturn = getKnightAttacks(square) & (~b.piecesOf(color));
	return boardToReturn;

}