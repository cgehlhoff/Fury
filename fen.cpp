#include <string>
#include <sstream>
#include "types.h"
#include "board.h"


bool charToPiece(char c, Piece& outPiece, Color& outColor) {
	switch (c) {
		case 'P': outPiece = PAWN; outColor = WHITE; return true;
		case 'N': outPiece = KNIGHT; outColor = WHITE; return true;
		case 'B': outPiece = BISHOP; outColor = WHITE; return true;
		case 'R': outPiece = ROOK; outColor = WHITE; return true;
		case 'Q': outPiece = QUEEN; outColor = WHITE; return true;
		case 'K': outPiece = KING; outColor = WHITE; return true;
		case 'p': outPiece = PAWN; outColor = BLACK; return true;
		case 'n': outPiece = KNIGHT; outColor = BLACK; return true;
		case 'b': outPiece = BISHOP; outColor = BLACK; return true;
		case 'r': outPiece = ROOK; outColor = BLACK; return true;
		case 'q': outPiece = QUEEN; outColor = BLACK; return true;
		case 'k': outPiece = KING; outColor = BLACK; return true;
	}

	return false;

}

void parseBoardField(const std::string& boardField, Board& b) {

    std::istringstream iss(boardField);
    std::string rankString;
    int rankIndex = 7;

    while (std::getline(iss, rankString, '/')) {

        int file = 0;

        for (char c : rankString) {
            if (isdigit(c)) {
                file += (c - '0');
            }
            else {
                Piece piece;
                Color color;
                if (charToPiece(c, piece, color)) {
                    int square = rankIndex * 8 + file;
                    b.pieces[color][piece] |= (1ULL << square);
                    file++;
                }
            }
        }

        rankIndex--;
    }
}

Color parseFEN(const std::string& fen, Board& b) {

    // start empty; FEN only specifies occupied squares
    for (int c = 0; c < NUM_COLORS; c++)
        for (int p = 0; p < NUM_PIECE_TYPES; p++)
            b.pieces[c][p] = 0ULL;

    // splits the FEN into its 6 whitespace-separated fields
    std::istringstream iss(fen);
    std::string boardField, sideField, castleField, epField, halfmoveField, fullmoveField;
    iss >> boardField >> sideField >> castleField >> epField >> halfmoveField >> fullmoveField;

    // board layout
    parseBoardField(boardField, b);

    // side to move
    Color sideToMove = (sideField == "w") ? WHITE : BLACK;

    // castling rights
    b.whiteCanCastleKingside = false;
    b.whiteCanCastleQueenside = false;
    b.blackCanCastleKingside = false;
    b.blackCanCastleQueenside = false;

    for (char c : castleField) {
        if (c == 'K') b.whiteCanCastleKingside = true;
        if (c == 'Q') b.whiteCanCastleQueenside = true;
        if (c == 'k') b.blackCanCastleKingside = true;
        if (c == 'q') b.blackCanCastleQueenside = true;
    }

    // en passant target square, or none
    if (epField == "-") {
        b.enPassantTarget = std::nullopt;
    }
    else {
        int file = epField[0] - 'a';
        int rank = epField[1] - '1';
        b.enPassantTarget = rank * 8 + file;
    }

    // halfmove/fullmove counters not tracked yet

    return sideToMove;
}