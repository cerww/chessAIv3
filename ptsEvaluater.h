#ifndef PTSEVAL_H
#define PTSEVAL_H
#include "bitBoard.h"
#include <utility>
enum idkWhatToNameThis {
	ATTACK,
	DEFEND,
	EXIST
};

struct points {
	int32_t black = 0;
	int32_t white = 0;
};

class ptsEvaluater {
public:
	ptsEvaluater(bitBoard);
	points evaluate();
	static unsigned N;
private:
	bitBoard m_board;
	struct getMovesPtsOutput {
		uint32_t whiteAttack = 0;
		uint32_t whiteDefend = 0;
		uint32_t whiteMoves = 0;
		uint32_t whiteMat = 0;

		uint32_t blackAttack = 0;
		uint32_t blackDefend = 0;
		uint32_t blackMoves = 0;
		uint32_t blackMat = 0;
	};
	getMovesPtsOutput getMovesPts();

	template<idkWhatToNameThis m>
	static uint32_t getPieceVal(const int p);

	template<idkWhatToNameThis m>
	static uint32_t getPieceVal2(const bitBoard &b, int x, int y);
	
	uint64_t moveAbleWhite;// = UINT64_MAX;
	uint64_t moveAbleBlack;// = UINT64_MAX;
	std::array<std::array<uint32_t, 8>, 8> stuffs = {};
	std::pair<int, int> checkIfCheck();//first is black
	unsigned whiteKingSpot;// = (unsigned)log2(m_board.whiteKing);
	unsigned whitekingXpos;// = whiteKingSpot & 7;
	unsigned whitekingYpos;// = whiteKingSpot >> 3;

	unsigned blackKingSpot;// = (unsigned)log2(m_board.blackKing);
	unsigned blackKingXpos;// = whiteKingSpot & 7;
	unsigned blackKingYpos;// = whiteKingSpot >> 3;
	template<color m>
	int checkCheck();
	void doKingStuff(getMovesPtsOutput&,uint64_t,uint64_t);
};


/*
check if check,
if not check -> look at x-rays to king
*/

#endif

