#include <cstdint>
#include "types.h"

uint64_t getKnightAttacks(int square) {
	
	uint64_t boardToReturn = 0ULL;
	int file = square % 8;
	int rank = square / 8;
	int newRank = 0, newFile = 0;

	int rankDeltas[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int fileDeltas[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	for (int i = 0; i < 8; i++) {
		newRank = rank + rankDeltas[i];
		newFile = file + fileDeltas[i];
		if (newRank > -1 && newRank < 8 && newFile > -1 && newFile < 8) {
			boardToReturn |= (1ULL << (8 * newRank + (newFile)));
		}
	}

	return boardToReturn;

}

uint64_t getKingAttacks(int square) {

	uint64_t boardToReturn = 0ULL;
	int file = square % 8;
	int rank = square / 8;
	int newRank = 0;
	int newFile = 0;

	int rankDeltas[8] = { 1, 1, 0, -1, -1, -1, 0, 1};
	int fileDeltas[8] = { 0, 1, 1, 1, 0, -1, -1, -1};

	for (int i = 0; i < 8; i++) {
		newRank = rank + rankDeltas[i];
		newFile = file + fileDeltas[i];
		if (newRank > -1 && newRank < 8 && newFile > -1 && newFile < 8) {
			boardToReturn |= (1ULL << (8 * newRank + (newFile)));
		}
	}

	return boardToReturn;

}