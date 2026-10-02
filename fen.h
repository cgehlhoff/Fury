#pragma once
#include <string>
#include "types.h"
#include "board.h"

bool charToPiece(char c, Piece& outPiece, Color& outColor);
void parseBoardField(const std::string& boardField, Board& b);
Color parseFEN(const std::string& fen, Board& b);