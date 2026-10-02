#pragma once
#include <cstdint>
#include <vector>

uint64_t getKnightMoves(int square, Color color, const Board& b);
uint64_t getKingMoves(int square, Color color, const Board& b);
uint64_t getRookMoves(int square, Color color, const Board& b);
uint64_t getBishopMoves(int square, Color color, const Board& b);
uint64_t getQueenMoves(int square, Color color, const Board& b);
uint64_t getPawnPushes(int square, Color color, const Board& b);
uint64_t getPawnMoves(int square, Color color, const Board& b);
bool isSquareAttacked(int square, Color color, const Board& b);
uint64_t filterLegalMoves(int from, Piece piece, Color color, uint64_t psuedoMoves, Board& b);
std::vector<Move> generateAllMoves(Color color, Board& b);
uint64_t perft(int depth, Color color, Board& b);
bool canCastleKingside(Color color, const Board& b);
bool canCastleQueenside(Color color, const Board& b);