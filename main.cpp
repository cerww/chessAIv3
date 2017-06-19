#include <iostream>
#include "chessAI.h"
#include <string>
#include "timeStuff.h"
#include "ai.h"
#include <utility>
#include <bitset>

int main() {
	/*
	std::pair<cw::vector2<char>, cw::vector2<char>> a;
	chessB b;
	for (int i = 0; i<8; ++i) {
		b.b[i][1] = Cpiece(pieceName::PAWN, pieceColor::BLACK);
		b.b[i][6] = Cpiece(pieceName::PAWN, pieceColor::WHITE);
		for (int y = 2; y<6; ++y) {
			//b.b[i][y] = Cpiece(pieceName::NONE, pieceColor::NONE);
		}
	}
	b.b[0][0] = Cpiece(pieceName::ROOK, pieceColor::BLACK);
	b.b[1][0] = Cpiece(pieceName::HORSE, pieceColor::BLACK);
	b.b[2][0] = Cpiece(pieceName::BISHOP, pieceColor::BLACK);
	b.b[3][4] = Cpiece(pieceName::QUEEN, pieceColor::BLACK);
	b.b[4][0] = Cpiece(pieceName::KING, pieceColor::BLACK);
	b.b[5][2] = Cpiece(pieceName::BISHOP, pieceColor::BLACK);
	b.b[2][4] = Cpiece(pieceName::HORSE, pieceColor::BLACK);
	b.b[7][2] = Cpiece(pieceName::ROOK, pieceColor::WHITE);

	b.b[0][7] = Cpiece(pieceName::ROOK, pieceColor::WHITE);
	b.b[1][7] = Cpiece(pieceName::HORSE, pieceColor::WHITE);
	b.b[2][7] = Cpiece(pieceName::BISHOP, pieceColor::WHITE);
	b.b[2][5] = Cpiece(pieceName::QUEEN, pieceColor::WHITE);
	b.b[4][7] = Cpiece(pieceName::KING, pieceColor::WHITE);
	b.b[5][4] = Cpiece(pieceName::BISHOP, pieceColor::WHITE);
	b.b[6][5] = Cpiece(pieceName::HORSE, pieceColor::WHITE);
	b.b[7][3] = Cpiece(pieceName::ROOK, pieceColor::WHITE);

	timeTest h;
	h.start();
	//chessAI ai;
	
	//ai.run(b, &a);
	std::cout << (int)a.first.x << " " << (int)a.first.y << "\n" << (int)a.second.x << " " << (int)a.second.y << std::endl;
	h.end();
	*/

	//AI AI2;
	bitBoard b2 = {};
	for (int i = 0; i < 8; ++i) {
		setSpot(b2.blackPawns, i, 1, 1);
		setSpot(b2.whitePawns, i, 6, 1);
	}
	setSpot(b2.whiteRooks, 7, 7, 1);
	setSpot(b2.whiteHorse, 6, 7, 1);
	setSpot(b2.whiteBish, 5, 7, 1);
	setSpot(b2.whiteKing, 4, 7, 1);
	setSpot(b2.whiteQueen, 3, 7, 1);
	setSpot(b2.whiteBish, 2, 7, 1);
	setSpot(b2.whiteHorse, 1, 7, 1);
	setSpot(b2.whiteRooks, 0, 7, 1);
	
	setSpot(b2.blackRooks, 7, 0, 1);
	setSpot(b2.blackHorse, 6, 0, 1);
	setSpot(b2.blackBish, 5, 0, 1);
	setSpot(b2.blackKing, 4, 0, 1);
	setSpot(b2.blackQueen, 3, 0, 1);
	setSpot(b2.blackBish, 2, 0, 1);
	setSpot(b2.blackHorse, 1, 0, 1);
	setSpot(b2.blackRooks, 0, 0, 1); 
	//setSpot(b2.blackRooks, 0, 0, 0);
	//setPts(b2);
	std::cout << std::bitset<64>(b2.getFullBoard()).to_string() << std::endl;
	std::cout << ((b2.getWhitePieces() >> (2 * 8)) & 128ull);
	//printf("%b\n",b2.whiteRooks);
	AI ai2(b2);
	auto a = ai2.start();
	std::cout << (int)a.first.x << ' ' << (int)a.first.y << '\n' << (int)a.second.x << ' ' << (int)a.second.y<<'\n';
	std::cout << "done" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}

