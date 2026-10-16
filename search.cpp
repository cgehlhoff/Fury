#include <vector>
#include <climits>
#include <optional>
#include "move.h"
#include "board.h"
#include "types.h"
#include "attacks.h"
#include "movegen.h"

const int MATE_SCORE = 100000;

int evaluate(const Board& b, Color color) {

	int pieceValues[NUM_PIECE_TYPES] = { 100, 300, 300, 500, 900, 0 };
	int myTotal = 0;
	int opponentTotal = 0;
	Color opponentColor = (color == WHITE) ? BLACK : WHITE;

	for (int pieceType = 0; pieceType < NUM_PIECE_TYPES; pieceType++) {
		myTotal += popcount(b.pieces[color][pieceType]) * pieceValues[pieceType];
	}
	for (int pieceType = 0; pieceType < NUM_PIECE_TYPES; pieceType++) {
		opponentTotal += popcount(b.pieces[opponentColor][pieceType]) * pieceValues[pieceType];
	}

	return myTotal - opponentTotal;

}

// alpha beta
int negamax(int depth, int alpha, int beta, Color color, Board& b) {
    if (depth == 0) {
        return evaluate(b, color);
    }

    Color oppositeColor = (color == WHITE) ? BLACK : WHITE;

    std::vector<Move> moves = generateAllMoves(color, b);

    if (moves.empty()) {
        bool inCheck = isSquareAttacked(bitscan(b.pieces[color][KING]), oppositeColor, b);
        if (inCheck) {
            return -(MATE_SCORE + depth);   // checkmated: bad for the side to move; sooner mates (bigger depth) are worse for it
        }
        return 0;                           // stalemate: draw
    }

    for (Move m : moves) {
        MoveInfo info = b.makeMove(m.from, m.to, m.piece, color, m.promotionPiece);
        int currentScore = -negamax(depth - 1, -beta, -alpha, oppositeColor, b);
        b.unmakeMove(m.from, m.to, m.piece, color, info, m.promotionPiece);
        if (currentScore >= beta) {
            return beta;
        }
        if (currentScore > alpha) {
            alpha = currentScore;
        }
    }
    
    return alpha;

}

std::optional <Move> findBestMove(int depth, Color color, Board& b) {

    std::vector<Move> moves = generateAllMoves(color, b);
    int alpha = -1000000;
    int beta = 1000000;
    Color oppositeColor = (color == WHITE) ? BLACK : WHITE;

    if (moves.empty()) {
        return std::nullopt;   // checkmate or stalemate: nothing to play
    }

    Move bestMove = moves.at(0);

    for (Move m : moves) {
        MoveInfo info = b.makeMove(m.from, m.to, m.piece, color, m.promotionPiece);
        int currentScore = -negamax(depth - 1, -beta, -alpha, oppositeColor, b); // new parameters for negamax
        if (currentScore > alpha) {
            alpha = currentScore;
            bestMove = m;
        }
        b.unmakeMove(m.from, m.to, m.piece, color, info, m.promotionPiece);
    }

    return bestMove;
}