#include <cstdint>
#include "types.h"

#ifdef _MSC_VER
#include <intrin.h>

#endif // _MSC_VER


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

uint64_t getPawnAttacks(int square, Color color) {

	uint64_t boardToReturn = 0ULL;
	int file = square % 8;
	int rank = square / 8;
	int newRank = 0;
	int newFile = 0;
	int rankDelta = 1;

	int fileDeltas[2] = { -1, 1 };
	if (color == WHITE)
		rankDelta = 1;
	else
		rankDelta = -1;

	for (int i = 0; i < 2; i++) {
		newRank = rank + rankDelta;
		newFile = file + fileDeltas[i];
		if (newRank > -1 && newRank < 8 && newFile > -1 && newFile < 8) {
			boardToReturn |= (1ULL << (8 * newRank + (newFile)));
		}
	}

	return boardToReturn;

}

uint64_t getRookAttacks(int square, uint64_t occupied) {

	uint64_t boardToReturn = 0ULL;
	int file = square % 8;
	int rank = square / 8;
	int currentRank, currentFile;
	int deltaRanks[4] = { 1, 0, -1, 0 };
	int deltaFiles[4] = { 0, 1, 0, -1 };

	for (int i = 0; i < 4; i++) {
		currentRank = rank;
		currentFile = file;
		while (true) {
			currentRank += deltaRanks[i];
			currentFile += deltaFiles[i];
			if (currentRank > 7 || currentRank < 0 || currentFile > 7 || currentFile < 0) 
				break;
			boardToReturn |= (1ULL << (8 * currentRank + (currentFile)));
			if (occupied & (1ULL << (8 * currentRank + currentFile)))
				break;
		}
	}
	
	return boardToReturn;

}

uint64_t getBishopAttacks(int square, uint64_t occupied) {

	uint64_t boardToReturn = 0ULL;
	int file = square % 8;
	int rank = square / 8;
	int currentRank, currentFile;
	int deltaRanks[4] = { 1, -1, -1, 1 };
	int deltaFiles[4] = { 1, 1, -1, -1 };

	for (int i = 0; i < 4; i++) {
		currentRank = rank;
		currentFile = file;
		while (true) {
			currentRank += deltaRanks[i];
			currentFile += deltaFiles[i];
			if (currentRank > 7 || currentRank < 0 || currentFile > 7 || currentFile < 0)
				break;
			boardToReturn |= (1ULL << (8 * currentRank + (currentFile)));
			if (occupied & (1ULL << (8 * currentRank + currentFile)))
				break;
		}
	}

	return boardToReturn;

}

uint64_t getQueenAttacks(int square, uint64_t occupied) {
	uint64_t boardToReturn = 0ULL;

	boardToReturn |= getRookAttacks(square, occupied);
	boardToReturn |= getBishopAttacks(square, occupied);

	return boardToReturn;
}

int bitscan(uint64_t bitboard) {

#ifdef _MSC_VER
	unsigned long index;
	_BitScanForward64(&index, bitboard);
	return (int)index;

#else
	return __builtin_ctzll(bitboard);
#endif // _MSC_VER


}