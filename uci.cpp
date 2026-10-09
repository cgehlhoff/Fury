#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include "board.h"
#include "types.h"
#include "fen.h"
#include "search.h"
#include "uci.h"

static const std::string START_FEN =
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

static std::string squareName(int sq) {
    std::string s;
    s += (char)('a' + sq % 8);
    s += (char)('1' + sq / 8);
    return s;
}

static std::string moveToUci(const Move& m) {
    std::string s = squareName(m.from) + squareName(m.to);
    if (m.promotionPiece.has_value()) {
        switch (m.promotionPiece.value()) {
        case QUEEN:  s += 'q'; break;
        case ROOK:   s += 'r'; break;
        case BISHOP: s += 'b'; break;
        case KNIGHT: s += 'n'; break;
        default: break;
        }
    }
    return s;
}

// applies a move like "e2e4" or "e7e8q" for the given side
static void applyUciMove(const std::string& uci, Board& b, Color side) {
    int from = (uci[0] - 'a') + 8 * (uci[1] - '1');
    int to = (uci[2] - 'a') + 8 * (uci[3] - '1');

    Piece piece = PAWN;
    for (int p = 0; p < NUM_PIECE_TYPES; p++) {
        if (b.pieces[side][p] & (1ULL << from)) {
            piece = (Piece)p;
            break;
        }
    }

    std::optional<Piece> promo = std::nullopt;
    if (uci.size() == 5) {
        switch (uci[4]) {
        case 'q': promo = QUEEN;  break;
        case 'r': promo = ROOK;   break;
        case 'b': promo = BISHOP; break;
        case 'n': promo = KNIGHT; break;
        }
    }

    b.makeMove(from, to, piece, side, promo);
}

static void handlePosition(std::istringstream& iss, Board& b, Color& side) {
    std::string token;
    iss >> token;

    if (token == "startpos") {
        side = parseFEN(START_FEN, b);
        iss >> token;                       // "moves" if present
    }
    else if (token == "fen") {
        std::string fen;
        while (iss >> token && token != "moves") {
            fen += token + " ";
        }
        side = parseFEN(fen, b);
    }

    if (token == "moves") {
        std::string mv;
        while (iss >> mv) {
            applyUciMove(mv, b, side);
            side = (side == WHITE) ? BLACK : WHITE;
        }
    }
}

void uciLoop() {
    Board b;
    Color side = parseFEN(START_FEN, b);
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "uci") {
            std::cout << "id name Fury\n";
            std::cout << "id author Craig Gehlhoff\n";
            std::cout << "uciok" << std::endl;
        }
        else if (cmd == "isready") {
            std::cout << "readyok" << std::endl;
        }
        else if (cmd == "ucinewgame") {
            side = parseFEN(START_FEN, b);
        }
        else if (cmd == "position") {
            handlePosition(iss, b, side);
        }
        else if (cmd == "go") {
            std::optional<Move> best = findBestMove(4, side, b);
            if (best.has_value()) {
                std::cout << "bestmove " << moveToUci(best.value()) << std::endl;
            }
            else {
                std::cout << "bestmove 0000" << std::endl;
            }
        }
        else if (cmd == "quit") {
            break;
        }
    }
}