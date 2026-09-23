#pragma once
#include <cstdint>
#include "types.h"

uint64_t getKnightAttacks(int square);
uint64_t getKingAttacks(int square);
uint64_t getPawnAttacks(int square, Color color);
uint64_t getRookAttacks(int square, uint64_t occupied);