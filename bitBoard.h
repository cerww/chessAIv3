//#pragma once
#ifndef BITBOARD_H
#define BITBOARD_H
#include <cstdint>
#include <array>
#include "vectors2.h"
#include <iostream>
#include <bitset>
#include <vector>
#include "constants.h"
enum class pieces :char { WHITEPAWNS, WHITEHORSE, WHITEROOK, WHITEBISH, WHITEQUEENS, WHITEKING, BLACKPAWNS, BLACKHORSE, BLACKROOK, BLACKBISH, BLACKQUEENS, BLACKKING };
enum color :char { WHITE, BLACK };


class bitBoard {
public:
	bitBoard() = default;
	bitBoard(uint64_t wp, uint64_t wh, uint64_t wr, uint64_t wb,uint64_t wq, uint64_t wk,
		     uint64_t bp, uint64_t bh, uint64_t br, uint64_t bb,uint64_t bq, uint64_t bk):
		whitePawns(wp),	
		whiteHorse(wh),
		whiteRooks(wr),
		whiteBish(wb),
		whiteQueen(wq),
		whiteKing(wk),

		blackPawns(bp),		
		blackHorse(bh),
		blackRooks(br),
		blackBish(bb),
		blackQueen(bq),
		blackKing(bk){};
	union{
		struct{
			uint64_t whitePawns;
			uint64_t whiteHorse;
			uint64_t whiteRooks;
			uint64_t whiteBish;
			uint64_t whiteQueen;
			uint64_t whiteKing;

			uint64_t blackPawns;
			uint64_t blackHorse;
			uint64_t blackRooks;
			uint64_t blackBish;
			uint64_t blackQueen;
			uint64_t blackKing;
		};
		//uint64_t allPieces[12];
		std::array<uint64_t,12> allPieces;
	};
	//cw::vector2s pts = {0,0};
	const uint64_t getFullBoard()const {
		return whitePawns | whiteQueen | whiteKing | whiteHorse | whiteRooks | whiteBish | 
			   blackPawns | blackQueen | blackKing | blackHorse | blackRooks | blackBish;
	}
	const uint64_t getWhitePieces()const {
		return whitePawns | whiteQueen | whiteKing | whiteHorse | whiteRooks | whiteBish;
	}
	const uint64_t getBlackPieces()const {
		return blackPawns | blackQueen | blackKing | blackHorse | blackRooks | blackBish;
	}
};
bool getSpot(const uint64_t& b,const uint8_t x,const uint8_t y);

inline void setSpot(uint64_t& b,int8_t x,int8_t y,bool c) {
	b &= ~(1ull << (y * 8 + x));
	b |= ((uint64_t)c) << (y * 8 + x);
}

uint64_t setPts2(const bitBoard & b);
uint64_t getPieceVal2(const bitBoard&,int x,int y);

uint64_t getPieceVal(const int p);//gets the value of a piece
bitBoard moveSpot(bitBoard b, const int8_t x1, const int8_t y1, const int8_t x2, const int8_t y2); 

template<color m>
std::vector<bitBoard> getBoards(const bitBoard &b);

std::vector<bitBoard> pruneBlack(std::vector<bitBoard>&&);

std::vector<bitBoard> pruneWhite(std::vector<bitBoard>&&);


inline int numThings(uint64_t thing) {
	int re = 0;
	while (thing) {
		int a = log2(thing);
		thing -= pow(2, a);
		++re;
	}return re;
}


inline int numThings2(uint64_t thing) {
	int re = 0;
	while (thing) {
		re += thing & 1;
		thing >>= 1;
	}
	return re;
}

inline bool operator==(const bitBoard& lhs,const bitBoard& rhs) {
	for (int i = 0; i < 12; ++i) {
		if (lhs.allPieces[i] ^ rhs.allPieces[i]) {
			return false;
		}
	}
	return true;
}

namespace std {
	template<>
	class hash<bitBoard> {
	public:
		size_t operator()(const bitBoard& b)const {
			hash<uint64_t> a;
			return a(b.getFullBoard()*47);
		}
	};
};
#endif

