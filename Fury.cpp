// Fury.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum COLOR {WHITE, BLACK};
enum PIECE {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NUM_PIECE_TYPES};
enum SQUARE {A1, B1, C1, D1, E1, F1, G1, H1,
             A2, B2, C2, D2, E2, F2, G2, H2,
             A3, B3, C3, D3, E3, F3, G3, H3,
             A4, B4, C4, D4, E4, F4, G4, H4};

struct Board {
    uint64_t pieces[2][NUM_PIECE_TYPES];

    public : void buildBoard() {
        pieces[WHITE][PAWN] = 0x000000000000FF00;
        pieces[WHITE][KNIGHT] = 0x0000000000000042;
        pieces[WHITE][BISHOP] = 0x0000000000000024;
        pieces[WHITE][ROOK] = 0x0000000000000081;
        pieces[WHITE][QUEEN] = 0x00000000000008;
        pieces[WHITE][KING] = 0x00000000000010;

        pieces[BLACK][PAWN] = 0x00FF000000000000;
        pieces[BLACK][KNIGHT] = 0x4200000000000000;
        pieces[BLACK][BISHOP] = 0x2400000000000000;
        pieces[BLACK][ROOK] = 0x8100000000000000;
        pieces[BLACK][QUEEN] = 0x0800000000000000;
        pieces[BLACK][KING] = 0x1000000000000000;
    }

};

int main()
{

    Board board;



    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
