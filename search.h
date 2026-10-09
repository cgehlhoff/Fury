#pragma once
#include <optional>
#include "board.h"
#include "types.h"
#include "attacks.h"

int evaluate(Board b, Color color);
int negamax(int depth, Color color, Board& b);
std::optional <Move> findBestMove(int depth, Color color, Board& b);