#include "ai.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <algorithm>
bool AI::done = 0;

class bitBoardCompFunctor {
public:
	bool operator()(const bitBoard& first, const bitBoard& second) {		
		auto firstIt = scores.find(first);
		if (firstIt == scores.end()) {
			ptsEvaluater pt(first);
			const auto asd = pt.evaluate();
			firstIt = scores.insert({ first,asd.black - asd.white }).first;
		}

		auto secondIt = scores.find(second);
		if (secondIt == scores.end()) {
			ptsEvaluater pt(second);
			const auto asd = pt.evaluate();
			secondIt = scores.insert({ second,asd.black - asd.white }).first;
		}
		return firstIt->second > secondIt->second;		
	}
	static void clearScoresTable() {
		std::cout << scores.size() << std::endl;
		scores.clear();
	};
	static void startReserve() {
		scores.reserve(30*30*30);
	}
private:
	static std::unordered_map<bitBoard, int32_t> scores;// = std::unordered_map<bitBoard, int32_t>();
};

std::unordered_map<bitBoard, int32_t> bitBoardCompFunctor::scores = {};

int32_t AI::miniMaxMIN(const bitBoard& b, alphaBeta2 ab,const int turns) {
	if(!b.blackKing)
		return INT32_MIN;
	if(!b.whiteKing)
		return INT32_MAX;
	if (turns == maxTurns) {
		ptsEvaluater pt(b);
		const auto asd = pt.evaluate();
		return asd.black - asd.white;
	}
	
	auto edges = (turns == 1 || turns == 3) ? (getBoards<color::WHITE>(b)) : getBoards<color::WHITE>(b);
	if (turns<5)
		std::stable_sort(edges.begin(), edges.end(), [](const bitBoard& first, const bitBoard& second) {
		bitBoardCompFunctor b;
		return !b(first, second); });
	
	int32_t val = INT32_MAX-1;
	
	for(const auto& i:edges){
		val = std::min(miniMaxMAX(i, ab, turns + 1), val);
		ab.beta = std::min(val, ab.beta);
		if (ab.beta <= ab.alpha) {
			return INT32_MIN;
		}
	}
	return val;
}

int32_t AI::miniMaxMAX(const bitBoard& b, alphaBeta2 ab,const int turns) {	
	if(!b.blackKing)
		return INT32_MIN;
	if(!b.whiteKing)
		return INT32_MAX;
	if (turns == maxTurns) {
		ptsEvaluater pt(b);
		const auto asd = pt.evaluate();
		return asd.black - asd.white;
	}
	auto edges = (turns == 2 || turns == 4) ? (getBoards<color::BLACK>(b)) : getBoards<BLACK>(b);
	if (turns<5)
		std::stable_sort(edges.begin(), edges.end(), [](const bitBoard& first,const bitBoard& second) {
		bitBoardCompFunctor comp;
		return comp(first, second);
	});
	int32_t val = INT32_MIN+1;
	
	for(const auto& i:edges){		
		val = std::max(miniMaxMIN(i, ab, turns + 1), val);
		ab.alpha = std::max(val, ab.alpha);
		if (ab.beta <= ab.alpha) {
			return INT32_MAX;
		}
	}return val;
}

std::pair<cw::vector2b, cw::vector2b> AI::start() {
	bitBoardCompFunctor::startReserve();
	//unsigned index = 0;
	int32_t val = INT32_MIN;
	auto edges = pruneBlack(getBoards<color::BLACK>(m_startingBoard));
	if(!edges.size())return {};
	alphaBeta2 ab;
	ab.beta = nullMoveThingy();
	ab.alpha = nullMoveThingy2();
	//const int numThreads = edges.size()-1;
	std::cout << edges.size() <<" things"<< std::endl;
	//std::cout<<std::bitset<64>(setPts2(m_startingBoard)>>32)<<std::endl;//display white pts
	unsigned index = 0;
	
	std::stable_sort(edges.begin(), edges.end(), bitBoardCompFunctor());
	for (unsigned i = 0; i < edges.size(); ++i) {
		const auto temp = miniMaxMIN(edges[i], ab, 1);
		val = std::max(val, temp);
		
		if (val == temp) {
			ab.alpha = std::max(val,ab.alpha);
			index = i;
		}std::cout << temp <<' '<<ab.alpha<<' '<< index<<std::endl;
	}
	//*/
	if(!edges.size()) return {};
	/*
	std::vector<int32_t> vals(edges.size());
	std::vector<std::thread> threads;
	std::vector<std::vector<int32_t>> vecVals(numThreads+1,std::vector<int32_t>((edges.size()/(numThreads+1)),INT32_MIN));
	//sectionSize = edges.size()/(t+1)
	for(int i = 0;i<numThreads;++i){
		threads.emplace_back([&](){
			int val = INT32_MIN;
			int t = i;
			//std::vector<int32_t>& veca = vecVals[t];
			
			alphaBeta2 ab;
			for (unsigned i = t*edges.size()/(numThreads+1); i < (t+1)*edges.size()/(numThreads+1); ++i) {
				const auto temp = miniMaxMIN(edges[i], ab, 1);
				val = awesome::max(val, temp);
				
				if (val == temp) {
					ab.alpha = awesome::max(val,ab.alpha);
					--ab.alpha;
					//index = i;
				}
				vals[i] = temp;
				//std::cout << temp <<' '<<ab.alpha<< std::endl;
			}
		});
	}std::cout<<"abc"<<std::endl;
	//alphaBeta2 ab;
	//auto& veca = vecVals.back();
	for (unsigned i = numThreads*edges.size()/(numThreads+1); i < edges.size(); ++i) {
		const auto temp = miniMaxMIN(edges[i], ab, 1);
		val = awesome::max(val, temp);
		
		if (val == temp) {
			ab.alpha = awesome::max(val,ab.alpha);
			--ab.alpha;
			//index = i;
		}//std::cout << temp <<' '<<ab.alpha<< std::endl;
		vals[i] = temp;
	}
	for(auto& i:threads){
		i.join();
	}
 
	
	for(unsigned i = 1;i<vals.size();++i){
		std::cout<<vals[i]<<std::endl;
		if(vals[i]>vals[index])
			index = i;
	}
	//*/	
	std::cout << index << std::endl;
	
	std::pair<cw::vector2b, cw::vector2b> moveSpots = { {0,0},{0,0} };
	for (int i = 0; i < 12; ++i) {
		const uint64_t a = m_startingBoard.allPieces[i] ^ edges[index].allPieces[i];
		if (m_startingBoard.allPieces[i] ^ edges[index].allPieces[i]){
			const long double tempyay = log2l(a);
			if (tempyay!=floor(tempyay)) {
				unsigned nums = 0;
				for (int8_t x = 0; x < 8; ++x) {
					for (int8_t y = 0; y < 8; ++y) {
						if (getSpot(a,x,y)) {
							if (!nums) {
								moveSpots.first = { x,y };
								nums = 1;
							}
							else {
								moveSpots.second = { x,y };
							}
						}
					}
				}
			}
		}
	}
	bitBoardCompFunctor::clearScoresTable();
	if(moveSpots.first == moveSpots.second) {//pawn promotion 
		const unsigned pawnSpot = log2((m_startingBoard.blackPawns ^ (edges[index].blackPawns)));
		moveSpots.first = { (char)(pawnSpot &7),(char)(pawnSpot >>3 )};
		
		const unsigned queenSpot = log2((m_startingBoard.blackQueen^ (edges[index].blackQueen)));
		moveSpots.second = { (char)(queenSpot &7),(char)(queenSpot>> 3) }; 
	}
	if (getSpot(edges[index].getBlackPieces(),moveSpots.first.x,moveSpots.first.y)) {
		return { moveSpots.second,moveSpots.first };
	}
	return moveSpots;
}

void AIrun(const bitBoard& b,std::pair<cw::vector2<int8_t>,cw::vector2<int8_t> >* toDoMove){
	AI ai(b);
	//auto c = ai.start();
	*toDoMove = ai.start();
	AI::done = 1;
}

int32_t AI::nullMoveThingy(){
	int32_t lowest = INT32_MIN;
	for (auto&& move1 : (getBoards<BLACK>(m_startingBoard))) {
		for (auto&& move2 : (getBoards<BLACK>(move1))) {
			//for (auto&& move3 : pruneBlack(getBoards<BLACK>(move2))) {
				ptsEvaluater eval(move2);
				const auto temp = eval.evaluate();
				lowest = std::max(lowest, temp.black - temp.white);
			//}
		}
	}return lowest;
}

int32_t AI::nullMoveThingy2() {
	int32_t lowest = INT32_MAX;
	for (auto&& move1 : (getBoards<WHITE>(m_startingBoard))) {
		for (auto&& move2 : (getBoards<WHITE>(move1))) {
			//for (auto&& move3 : pruneBlack(getBoards<BLACK>(move2))) {
			ptsEvaluater eval(move2);
			const auto temp = eval.evaluate();
			lowest = std::min(lowest, temp.black - temp.white);
			//}
		}
	}return lowest;
}
