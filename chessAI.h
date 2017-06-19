#ifndef CHESSAI_H
#define CHESSAI_H
#include <thread>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include "chessPiece.h"
//#include <SFML/Graphics.hpp>
#include "vectors2.h"
#include <memory>
#include <algorithm>
#include "vecFuncs.h"
#include <array>
/*
enum class pieceColor :char { WHITE, BLACK, NONE };
enum class pieceName :char { PAWN, ROOK, BISHOP, QUEEN, KING, HORSE, NONE };//*/
																			//000 000 00
struct Cpiece {
	Cpiece() {};//:n((pieceName)0),c((pieceColor)0){};
	Cpiece(pieceName k, pieceColor l) :all((unsigned char)l | ((unsigned char)k << 2)) {}//:n(k),c(l){};
																						 //pieceName n;
	unsigned char all;
	pieceName n()const { return (pieceName)(all >> 2); };
	pieceColor c()const { return (pieceColor)(all % 4); };
};

inline bool operator==(const Cpiece a, const Cpiece other) {
	return a.all == other.all;
}

struct chessB {
	chessB() {};
	std::array<std::array<Cpiece, 8>, 8 > b;
	mutable cw::vector2<uint16_t> pts = { UINT16_MAX,UINT16_MAX };
};

inline bool operator ==(const chessB& one, const chessB& other) {
	return one.b == other.b;
}

namespace std {
	template <>
	class hash<chessB> {
	public:
		size_t operator()(const chessB &a) const {
			string k;
			k.resize(64);
			for (int x = 0; x<8; ++x)
				for (int y = 0; y<8; ++y) {
					k[(x * 8) + y] = ((char)(a.b[x][y].n())) + 65;
				}
			return hash<string>()(k);
		}
	};
};

struct Bpoints {
	int white = 0;
	int black = 0;
	int operator[](int o);
};

inline int Bpoints::operator[](int o) {
	if (o == 0)return white;
	return black;
}

struct boardNode {
	boardNode(const chessB& c, std::vector<std::pair<cw::vector2<char>, cw::vector2<char>>>& b) :board(c),moveSpots(std::move(b)){}
	//boardNode() = default;
	const chessB board;
	const std::vector<std::pair<cw::vector2<char>, cw::vector2<char>>> moveSpots;
};

inline bool operator==(const boardNode& one, const boardNode& two) {
	return one.board == two.board;
}

namespace std {
	template<>
	class hash<boardNode> {
	public:
		size_t operator()(const boardNode& a)const {
			return hash<chessB>()(a.board);
		}
	};
};

struct alphaBeta{
	alphaBeta() = default;
	int16_t alpha = INT16_MIN;
	int16_t beta = INT16_MAX;	
};

class chessAI {
public:
	static void run(const chessB b, std::pair<cw::vector2<int8_t>, cw::vector2<int8_t>>* toDoMove);

	int numNodes;
	static int done;
private:
	static std::vector<cw::vector2<char>> getMoveSpots(const chessB& b, const Cpiece& p,const cw::vector2<char> spot);

	static boardNode makeNode2(const chessB& b,const pieceColor);
	static void spotMove(const std::pair<cw::vector2<char>, cw::vector2<char>>& move, chessB& board);

	static int16_t traverseTree2(const chessB& b,const int turns,alphaBeta, std::unordered_map<chessB, std::vector<int16_t> >* visited);
	//int16_t traverseTree2(const chessB& b, const int turns, ska::flat_hash_map<chessB, std::vector<std::vector<int16_t> > >* visited);

	static std::pair<cw::vector2<char>, cw::vector2<char> > getThingy2(const chessB& c);
	static cw::vector2<uint16_t> getP2(const chessB& board);

};

#endif

