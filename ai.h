//#pragma once
#ifndef AI_H
#define AI_H
#include "bitBoard.h"
#include "vectors2.h"
#include "ptsEvaluater.h"
#include <vector>
#include "alphaBeta.h"

const int maxTurns = 7;


enum class minMax:char {MIN,MAX};
class AI {
public:
	AI() = default;
	AI(bitBoard b) :m_startingBoard(std::move(b)) {};
	std::pair<cw::vector2b, cw::vector2b> start();
	static bool done;
private:
	bitBoard m_startingBoard;
	
	int32_t miniMaxMIN(const bitBoard&, alphaBeta2,const int turns);

	//template<>
	int32_t miniMaxMAX(const bitBoard&, alphaBeta2,const int turns);
	
	int32_t nullMoveThingy();
	int32_t nullMoveThingy2();
};

void AIrun(const bitBoard&,std::pair<cw::vector2<int8_t>,cw::vector2<int8_t> >*); 
#endif
