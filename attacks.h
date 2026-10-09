#pragma once
#include <cstdint>
#include "types.h"

uint64_t getKnightAttacks(int square);
uint64_t getKingAttacks(int square);
uint64_t getPawnAttacks(int square, Color color);
uint64_t getRookAttacks(int square, uint64_t occupied);
uint64_t getBishopAttacks(int square, uint64_t occupied);
uint64_t getQueenAttacks(int square, uint64_t occupied);
int bitscan(uint64_t bitboard);
int popcount(uint64_t bitboard);