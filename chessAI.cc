#include "chessAI.h"
#include <iostream>
#include <deque>
//#include "flat_hash_map.hpp"

const int TURNSY = 7;
#define TEST_START std::cout<<"b"<<std::endl;
#define TEST_END std::cout<<"a"<<std::endl;
int chessAI::done = 0;
std::vector<cw::vector2<char>> chessAI::getMoveSpots(const chessB& b, const Cpiece& p,const cw::vector2<char> spot) {
	std::vector<cw::vector2<char> > moveSpots;
	if (p.n() == pieceName::NONE) {
		return {};
	}
	else if (p.n() == pieceName::PAWN) {
		moveSpots.reserve(2);
		if (p.c() == pieceColor::BLACK) {
			for (int x = 1; x<(spot.y == 1 ? 3 : 2); ++x) {
				if (b.b[spot.x][spot.y + x].n() == pieceName::NONE)
					moveSpots.emplace_back(spot.x, spot.y + x);
				else break;
			}
			if (spot.x != 7) {
				if (b.b[spot.x + 1][spot.y + 1].c() == pieceColor::WHITE&&b.b[spot.x + 1][spot.y + 1].n() != pieceName::NONE) {
					moveSpots.emplace_back(spot.x + 1, (spot.y + 1));
					//board.board[spot.x+1].at(spot.y+1).k[this] = something();
				}
			}
			else if (spot.x != 0) {
				if (b.b[spot.x - 1][spot.y + 1].c() == pieceColor::WHITE&&b.b[spot.x - 1][spot.y + 1].n() != pieceName::NONE) {
					moveSpots.emplace_back(spot.x - 1, spot.y + 1);
					//board.board[spot.x-1].at(spot.y+1).k[this] = something();
				}
			}
		}
		else {
			for (int x = 1; x<(spot.y == 6 ? 3 : 2); ++x) {
				if (b.b[spot.x][spot.y - x].n() == pieceName::NONE)
					moveSpots.emplace_back(spot.x, spot.y - x);
				else break;
			}
			if (spot.x != 7) {
				if (b.b[spot.x + 1][spot.y - 1].c() == pieceColor::BLACK&&b.b[spot.x + 1][spot.y - 1].n() != pieceName::NONE) {
					moveSpots.emplace_back(spot.x + 1, spot.y - 1);
					//board.board[spot.x+1].at(spot.y-1).k[this] = something();
				}
			}
			else if (spot.x != 0) {
				if (b.b[spot.x - 1][spot.y - 1].c() == pieceColor::BLACK&&b.b[spot.x - 1][spot.y - 1].n() != pieceName::NONE) {
					moveSpots.emplace_back(spot.x - 1, spot.y - 1);
					//board.board[spot.x-1].at(spot.y-1).k[this] = something();
				}
			}
		}
	}//else if(p.n()==pieceName::BISHOP){}
	else if (p.n() == pieceName::ROOK) {
		moveSpots.reserve(15);
		for (int x = spot.x + 1; x<8; ++x) {
			if (b.b[x][spot.y].n() == pieceName::NONE)
				//moveableSpots[x][spot.y]=1;
				moveSpots.emplace_back(x, spot.y);
			else if (b.b[x][spot.y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(x, spot.y);
				break;
			}
		}
		for (int x = spot.x - 1; x >= 0; --x) {
			if (b.b[x][spot.y].n() == pieceName::NONE)
				moveSpots.emplace_back(x, spot.y);
			else if (b.b[x][spot.y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(x, spot.y);
				break;
			}
		}
		for (int y = spot.y + 1; y<8; ++y) {
			if (b.b[spot.x][y].n() == pieceName::NONE)
				moveSpots.emplace_back(spot.x, y);
			else if (b.b[spot.x][y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(spot.x, y);
				break;
			}
		}
		for (int y = spot.y - 1; y >= 0; --y) {
			if (b.b[spot.x][y].n() == pieceName::NONE)
				moveSpots.emplace_back(spot.x, y);
			else if (b.b[spot.x][y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(spot.x, y);
				break;
			}
		}
	}
	else if (p.n() == pieceName::HORSE) {
		moveSpots.reserve(8);
		if (spot.x<7 && spot.y>1 && (b.b[spot.x + 1][spot.y - 2].c() != p.c() || b.b[spot.x + 1][spot.y - 2].n() == pieceName::NONE))moveSpots.emplace_back(spot.x + 1, spot.y - 2);
		if (spot.x<7 && spot.y<6 && (b.b[spot.x + 1][spot.y + 2].c() != p.c() || b.b[spot.x + 1][spot.y + 2].n() == pieceName::NONE))moveSpots.emplace_back(spot.x + 1, spot.y + 2);

		if (spot.x>0 && spot.y>1 && (b.b[spot.x - 1][spot.y - 2].c() != p.c() || b.b[spot.x - 1][spot.y - 2].n() == pieceName::NONE))moveSpots.emplace_back(spot.x - 1, spot.y - 2);
		if (spot.x>0 && spot.y<6 && (b.b[spot.x - 1][spot.y + 2].c() != p.c() || b.b[spot.x - 1][spot.y + 2].n() == pieceName::NONE))moveSpots.emplace_back(spot.x - 1, spot.y + 2);

		if (spot.x<6 && spot.y>0 && (b.b[spot.x + 2][spot.y - 1].c() != p.c() || b.b[spot.x + 2][spot.y - 1].n() == pieceName::NONE))moveSpots.emplace_back(spot.x + 2, spot.y - 1);
		if (spot.x<6 && spot.y<7 && (b.b[spot.x + 2][spot.y + 1].c() != p.c() || b.b[spot.x + 2][spot.y + 1].n() == pieceName::NONE))moveSpots.emplace_back(spot.x + 2, spot.y + 1);

		if (spot.x>1 && spot.y>0 && (b.b[spot.x - 2][spot.y - 1].c() != p.c() || b.b[spot.x - 2][spot.y - 1].n() == pieceName::NONE))moveSpots.emplace_back(spot.x - 2, spot.y - 1);
		if (spot.x>1 && spot.y<7 && (b.b[spot.x - 2][spot.y + 1].c() != p.c() || b.b[spot.x - 2][spot.y + 1].n() == pieceName::NONE))moveSpots.emplace_back(spot.x - 2, spot.y + 1);
	}
	else if (p.n() == pieceName::BISHOP) {
		moveSpots.reserve(15);
		//+x +y
		for (int c = 1; c + spot.x<8 && c + spot.y<8; ++c) {
			if (b.b[c + spot.x][c + spot.y].n() == pieceName::NONE) {
				moveSpots.emplace_back(c + spot.x, c + spot.y);
				continue;
			}
			if (b.b[c + spot.x][c + spot.y].c() == p.c())
				break;
			if (b.b[c + spot.x][c + spot.y].c() != p.c()) {
				moveSpots.emplace_back(c + spot.x, c + spot.y);
				break;
			}
		}
		//-x -y
		for (int c = 1; spot.x - c >= 0 && spot.y - c >= 0; ++c) {
			if (b.b[spot.x - c][spot.y - c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x - c, spot.y - c);
				continue;
			}
			if (b.b[spot.x - c][spot.y - c].c() == p.c())
				break;
			if (b.b[spot.x - c][spot.y - c].c() != p.c()) {
				moveSpots.emplace_back(spot.x - c, spot.y - c);
				break;
			}
		}
		//+x -y
		for (int c = 1; spot.x + c<8 && spot.y - c >= 0; ++c) {
			if (b.b[spot.x + c][spot.y - c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x + c, spot.y - c);
				continue;
			}
			if (b.b[spot.x + c][spot.y - c].c() == p.c())
				break;
			if (b.b[spot.x + c][spot.y - c].c() != p.c()) {
				moveSpots.emplace_back(spot.x + c, spot.y - c);
				break;
			}
		}
		//-x +y
		for (int c = 1; spot.x - c >= 0 && spot.y + c<8; ++c) {
			if (b.b[spot.x - c][spot.y + c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x - c, spot.y + c);
				continue;
			}
			if (b.b[spot.x - c][spot.y + c].c() == p.c())
				break;
			if (b.b[spot.x - c][spot.y + c].c() != p.c()) {
				moveSpots.emplace_back(spot.x - c, spot.y + c);
				break;
			}
		}
	}//4,0
	else if (p.n() == pieceName::QUEEN) {
		moveSpots.reserve(31);
		for (int c = 1; c + spot.x<8 && c + spot.y<8; ++c) {
			if (b.b[c + spot.x][c + spot.y].n() == pieceName::NONE) {
				moveSpots.emplace_back(c + spot.x, c + spot.y);
				continue;
			}
			if (b.b[c + spot.x][c + spot.y].c() == p.c()) {
				break;
			}
			if (b.b[c + spot.x][c + spot.y].c() != p.c()) {
				moveSpots.emplace_back(c + spot.x, c + spot.y);
				break;
			}
		}
		//-x -y
		for (int c = 1; spot.x - c >= 0 && spot.y - c >= 0; ++c) {
			if (b.b[spot.x - c][spot.y - c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x - c, spot.y - c);
				continue;
			}
			if (b.b[spot.x - c][spot.y - c].c() == p.c())
				break;
			if (b.b[spot.x - c][spot.y - c].c() != p.c()) {
				moveSpots.emplace_back(spot.x - c, spot.y - c);
				break;
			}
		}
		//+x -y
		for (int c = 1; spot.x + c<8 && spot.y - c >= 0; ++c) {
			if (b.b[spot.x + c][spot.y - c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x + c, spot.y - c);
				continue;
			}
			if (b.b[spot.x + c][spot.y - c].c() == p.c())
				break;
			if (b.b[spot.x + c][spot.y - c].c() != p.c()) {
				moveSpots.emplace_back(spot.x + c, spot.y - c);
				break;
			}
		}
		//-x +y
		for (int c = 1; spot.x - c >= 0 && spot.y + c<8; ++c) {
			if (b.b[spot.x - c][spot.y + c].n() == pieceName::NONE) {
				moveSpots.emplace_back(spot.x - c, spot.y + c);
				continue;
			}
			if (b.b[spot.x - c][spot.y + c].c() == p.c())
				break;
			if (b.b[spot.x - c][spot.y + c].c() != p.c()) {
				moveSpots.emplace_back(spot.x - c, spot.y + c);
				break;
			}
		}
		//rook part
		for (int x = spot.x + 1; x<8; ++x) {
			if (b.b[x][spot.y].n() == pieceName::NONE)
				//moveableSpots[x][spot.y]=1;
				moveSpots.emplace_back(x, spot.y);
			else if (b.b[x][spot.y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(x, spot.y);
				break;
			}
		}
		for (int x = spot.x - 1; x >= 0; --x) {
			if (b.b[x][spot.y].n() == pieceName::NONE)
				moveSpots.emplace_back(x, spot.y);
			else if (b.b[x][spot.y].c() == p.c()) {
				break;
			}
			else {//std::cout<<"abc"<<std::endl;
				moveSpots.emplace_back(x, spot.y);
				break;
			}
		}
		for (int y = spot.y + 1; y<8; ++y) {
			if (b.b[spot.x][y].n() == pieceName::NONE)
				moveSpots.emplace_back(spot.x, y);
			else if (b.b[spot.x][y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(spot.x, y);
				break;
			}
		}
		for (int y = spot.y - 1; y >= 0; --y) {
			if (b.b[spot.x][y].n() == pieceName::NONE)
				moveSpots.emplace_back(spot.x, y);
			else if (b.b[spot.x][y].c() == p.c()) {
				break;
			}
			else {
				moveSpots.emplace_back(spot.x, y);
				break;
			}
		}
	}
	else if (p.n() == pieceName::KING) {
		moveSpots.reserve(8);
		if (spot.x != 7) {
			if (spot.y != 7 && (b.b[spot.x + 1][spot.y + 1].c() != p.c() || b.b[spot.x + 1][spot.y + 1].n() == pieceName::NONE))
				moveSpots.emplace_back(spot.x + 1, spot.y + 1);
			if ((b.b[spot.x + 1][spot.y].c() != p.c() || b.b[spot.x + 1][spot.y].n() == pieceName::NONE))
				moveSpots.emplace_back(spot.x + 1, spot.y);
			if (spot.y != 0 && (b.b[spot.x + 1][spot.y - 1].c() != p.c() || b.b[spot.x + 1][spot.y - 1].n() == pieceName::NONE))
				moveSpots.emplace_back(spot.x + 1, spot.y - 1);
		}
		if (spot.x != 0) {
			if (spot.y != 7 && (b.b[spot.x - 1][spot.y + 1].c() != p.c() || b.b[spot.x - 1][spot.y + 1].n() == pieceName::NONE))
				moveSpots.emplace_back(spot.x - 1, spot.y + 1);
			if (b.b[spot.x - 1][spot.y].c() != p.c() || b.b[spot.x - 1][spot.y].n() == pieceName::NONE)
				moveSpots.emplace_back(spot.x - 1, spot.y + 0);
			if (spot.y != 0 && (b.b[spot.x - 1][spot.y - 1].c() != p.c() || b.b[spot.x - 1][spot.y - 1].n() == pieceName::NONE))
				moveSpots.emplace_back(spot.x - 1, spot.y - 1);
		}if (spot.y != 7 && (b.b[spot.x][spot.y + 1].c() != p.c() || b.b[spot.x][spot.y + 1].n() == pieceName::NONE))
			moveSpots.emplace_back(spot.x, spot.y + 1);
		if (spot.y != 0 && (b.b[spot.x][spot.y - 1].c() != p.c() || b.b[spot.x][spot.y - 1].n() == pieceName::NONE))
			moveSpots.emplace_back(spot.x, spot.y - 1);
	}
	//moveSpots.shrink_to_fit();
	return moveSpots;
}

int16_t getPieceValue(const pieceName p) {
	switch (p) {
	case pieceName::NONE:
		return 0;
	case pieceName::PAWN:
		return 1;
	case pieceName::BISHOP:
		return 3;
	case pieceName::HORSE:
		return 3;
	case pieceName::ROOK:
		return 5;
	case pieceName::QUEEN:
		return 9;
	case pieceName::KING:
		return 10000;
	}return 0;
}

boardNode chessAI::makeNode2(const chessB& b,const pieceColor currentTurn) {
	std::vector<std::pair<cw::vector2<char>, cw::vector2<char>> > n;
	n.reserve(32);
	for (int x = 0; x<8; ++x) {
		for (int y = 0; y<8; ++y) {
			if (b.b[x][y].n() == pieceName::NONE) 
				continue;
			if (currentTurn == pieceColor::BLACK&&b.b[x][y].c() == pieceColor::BLACK) {
				const std::vector<cw::vector2<char>> o = std::move(getMoveSpots(b, b.b[x][y], cw::vector2<char>(x, y)));
				for(unsigned i = 0;i<o.size();++i){
					n.emplace_back(cw::vector2<char>(x, y), o[i]);
				}
			}
			else if (currentTurn==pieceColor::WHITE&&b.b[x][y].c() == pieceColor::WHITE) {
				const std::vector<cw::vector2<char>> o = std::move(getMoveSpots(b, b.b[x][y], cw::vector2<char>(x, y)));
				for (unsigned i = 0;i<o.size();++i) {
					n.emplace_back(cw::vector2<char>(x, y), o[i]);
				}

			}
		}
	}

	return boardNode(b,n);
}

void chessAI::spotMove(const std::pair<cw::vector2<char>, cw::vector2<char>>& move, chessB& board) {
	if (board.b[(int)move.second.x][(int)move.second.y].c()==pieceColor::BLACK) {
		board.pts.x -= getPieceValue(board.b[(int)move.second.x][(int)move.second.y].n());
	}
	else {
		board.pts.y -= getPieceValue(board.b[(int)move.second.x][(int)move.second.y].n());
	}
	board.b[(int)move.second.x][(int)move.second.y] = board.b[(int)move.first.x][(int)move.first.y];
	board.b[(int)move.first.x][(int)move.first.y] = Cpiece(pieceName::NONE, pieceColor::NONE);
	if (board.b[move.second.x][move.second.y].n() == pieceName::PAWN&& move.second.y == (board.b[move.second.x][move.second.y].c() == pieceColor::BLACK ? 7 : 0)) {
		board.b[move.second.x][move.second.y].all = (board.b[move.second.x][move.second.y].all & 0b00000011) | 0b00001100;
		if (board.b[(int)move.second.x][(int)move.second.y].c() == pieceColor::BLACK) {
			board.pts.x += 48;
		}else {
			board.pts.y += 48;
		}
	}
}

int getPdiff(const cw::vector2<uint16_t> i) {
	return i.x - i.y;
}

cw::vector2<uint16_t> chessAI::getP2(const chessB& board) {
	if (board.pts.x != UINT16_MAX) {
		return board.pts;
	}
	for (int x = 0; x<8; ++x) {
		for (int y = 0; y<8; ++y) {
			if (board.b[x][y].n() == pieceName::NONE) {
				continue;
			}
			else if (board.b[x][y].c() == pieceColor::BLACK) {
				board.pts.x += getPieceValue(board.b[x][y].n());
			}
			else {
				board.pts.y += getPieceValue(board.b[x][y].n());
			}
		}
	}
	return board.pts;
}

//int16_t chessAI::traverseTree2(const chessB& b, const int turns, ska::flat_hash_map<chessB, std::vector<std::vector<int16_t> > >* visited) {

int16_t chessAI::traverseTree2(const chessB& b,const int turns,alphaBeta ab, std::unordered_map<chessB, std::vector<int16_t> >* visited) {
	if (turns == TURNSY) {
		return getPdiff(getP2(b));
	}
	const auto tempA = visited->find(b);
	if (tempA != visited->end()) {
		const int16_t vals = tempA->second[turns];
		if (vals != 30000) {
			//return vals;
		}
	}
	const auto nodey = std::move(makeNode2(b, (pieceColor)((turns % 2)+1<2)));
	const unsigned mko = nodey.moveSpots.size();

	if (!mko||getP2(nodey.board).x + getP2(nodey.board).y<12000) {
		return getPdiff(getP2(nodey.board));
	}
	int16_t val = (turns%2)?INT16_MAX:INT16_MIN;
	
	for (unsigned x = 0; x<mko; ++x) {
		chessB newB = b;
		spotMove(nodey.moveSpots[x], newB);
		//vals[x] = traverseTree2(newB, turns + 1,ab, visited);
		if(turns%2){
			val = std::min(traverseTree2(newB, turns + 1,ab, visited),val);
			ab.beta = std::min(val,ab.beta);
			if(ab.beta<=ab.alpha)
				return INT16_MIN;
				//break;	
		}else{	
			val = std::max(traverseTree2(newB, turns + 1,ab, visited),val);
			ab.alpha = std::max(ab.alpha,val);
			if(ab.beta<=ab.alpha)
				return INT16_MAX;
				//break;
		}
	}
	if (0&&turns < 6) {
		return val;
		auto& it = (*visited)[b];
		if (!(it.size()))
			it.resize(TURNSY ,30000);
		for (unsigned i = turns; i < it.size(); i += 2) {
			it[i] = val;
		}
	}
	return val;
}

std::pair<cw::vector2<char>, cw::vector2<char> > chessAI::getThingy2(const chessB& c) {
	const auto lol = makeNode2(c,pieceColor::BLACK);
	getP2(c);
	std::vector<int16_t> vecs(lol.moveSpots.size());
	std::unordered_map<chessB, std::vector<int16_t > > visited;
	
	alphaBeta ab;
	int16_t val = INT16_MIN;
	for (unsigned x = 0; x<lol.moveSpots.size(); ++x) {
		auto newB = c;
		spotMove(lol.moveSpots[x], newB);
		vecs[x] = traverseTree2(newB, 1,ab, &visited);
		val = std::max(vecs[x],val);
		ab.alpha = std::max(val,ab.alpha);
		std::cout<<val<<' '<<ab.alpha<<' '<<vecs[x]<<std::endl;
	}
	if (!vecs.size()) return std::pair<cw::vector2<char>, cw::vector2<char>>(cw::vector2<char>(0, 0), cw::vector2<char>(0, 0));

	unsigned highestIndex = 1;
	for (unsigned x = 1; x < vecs.size(); ++x) {
		if (vecs[x] >= vecs[highestIndex])
			highestIndex = x;
	}
	/*
	for (const auto& i : lol.moveSpots[0]) {
		std::cout << (int)i.first.x << ' ' << (int)i.first.y << '\n' << (int)i.second.x << ' ' << (int)i.second.y<<std::endl;
	}//*/
	return lol.moveSpots[highestIndex];
}


void chessAI::run(const chessB b, std::pair<cw::vector2<int8_t>, cw::vector2<int8_t>>* toDoMove) {
	//std::cout<<chessAI::dp2.size()<<std::endl;
	//auto c = makeNode(b);

	//*toDoMove = getThingy(c);
	//*toDoMove = getThingy2(b);
	std::cout<<"v4"<<std::endl;
	done = 1;
	//std::cout << "abc" << std::endl;
}



