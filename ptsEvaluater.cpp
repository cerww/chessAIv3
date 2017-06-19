#include "ptsEvaluater.h"
unsigned ptsEvaluater::N = 0;
#include "constants.h"

ptsEvaluater::ptsEvaluater(bitBoard b):m_board(std::move(b)){
	moveAbleBlack = m_board.getBlackPieces();
	moveAbleWhite = m_board.getWhitePieces();
	whiteKingSpot = (unsigned)log2(m_board.whiteKing);
	whitekingXpos = whiteKingSpot & 7;
	whitekingYpos = whiteKingSpot >> 3;

	blackKingSpot = (unsigned)log2(m_board.blackKing);
	blackKingXpos = whiteKingSpot & 7;
	blackKingYpos = whiteKingSpot >> 3;
	++N;
}
template<>
uint32_t ptsEvaluater::getPieceVal<EXIST>(const int p) {
	static constexpr int vals[12] = { 10,30,50,30,92,1000000,10,30,50,30,92,1000000 };
	return vals[p];
}

template<>
uint32_t ptsEvaluater::getPieceVal<ATTACK>(const int p) {
	static constexpr int vals[12] = { 0,4,8,4,8,0,0,4,8,4,8,0 };
	return vals[p];
}

template<>
uint32_t ptsEvaluater::getPieceVal<DEFEND>(const int p) {
	static constexpr int vals[12] = { 0,4,8,4,8,0,0,4,8,4,8,0 };
	return vals[p];
}

template<idkWhatToNameThis m>
uint32_t ptsEvaluater::getPieceVal2(const bitBoard & b, int x, int y) {
	if (!getSpot(b.getFullBoard(), x, y))
		return 0;
	for (unsigned i = 0; i < 12; ++i) {
		if (getSpot(b.allPieces[i], x, y))
			return getPieceVal<m>(i);
	}
	return 0;
}

points ptsEvaluater::evaluate(){
	if (!m_board.blackKing){
		points re;
		re.white = INT32_MIN+1;
		re.black = 0;
		return re;
	}	
	if (!m_board.whiteKing){
		points re;		
		re.black = INT32_MIN+1;
		re.white = 0;
		return re;
	}
	checkIfCheck();
	const auto pt = getMovesPts();
	points re;
	re.white += pt.whiteAttack*0.65 + pt.whiteDefend*0.65 + pt.whiteMoves + pt.whiteMat;
	re.black += pt.blackAttack*0.65 + pt.blackDefend*0.65 + pt.blackMoves + pt.blackMat;

	return re;
}

ptsEvaluater::getMovesPtsOutput ptsEvaluater::getMovesPts(){
	getMovesPtsOutput reVal;
	const auto fullBoard = m_board.getFullBoard();
	const auto whitePieces = m_board.getWhitePieces();
	const auto blackPieces = m_board.getBlackPieces();
	uint64_t whiteAttackable = 0;
	uint64_t blackAttackable = 0;

	for (unsigned y = 0; y < 8; ++y) {
		if (!((fullBoard >> 8 * y) & 255)) continue;
		for (unsigned x = 0; x < 8; ++x) {
			if (!((fullBoard >> (8 * y + x)) & 1)) continue;
			if ((whitePieces >> (8 * y + x)) & 1) {
				if ((m_board.whitePawns >> (y * 8 + x)) & 1) {
					reVal.whiteMat += getPieceVal<EXIST>(0);
					if (!((moveAbleWhite >> (y * 8 + x)) & 1))
						continue;
					if (x + 1 < 8) {
						if (getSpot(blackPieces, x + 1, y - 1)) {
							reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + 1, y - 1)+1;
							++reVal.whiteMoves;
						}
						else if (getSpot(whitePieces, x + 1, y - 1)) {
							reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x + 1, y - 1);
						}
						setSpot(whiteAttackable, x + 1, y - 1, 1);
					}
					if (x - 1 < 8) {
						if (getSpot(blackPieces, x - 1, y - 1)) {
							reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x - 1, y - 1)+1;
							++reVal.whiteMoves;
						}
						else if (getSpot(whitePieces, x - 1, y - 1)) {
							reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x - 1, y - 1);
						}
						setSpot(whiteAttackable, x - 1, y - 1, 1);
					}				
				}
				else if ((m_board.whiteBish >> (y * 8 + x)) & 1) {
					reVal.whiteMat += getPieceVal<EXIST>(1);
					if (!((moveAbleWhite >> (y * 8 + x)) & 1))
						continue;
					for (unsigned num = 0; num < 4; ++num) {
						for (int i = 1; (unsigned)(x + i*bishMove[num].x) < 8 && (unsigned)(y + i*bishMove[num].y) < 8; ++i) {
							if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								setSpot(whiteAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
								break;
							}
							else if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								++reVal.whiteMoves;
								setSpot(whiteAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
								break;
							}
							else {
								++reVal.whiteMoves;
								setSpot(whiteAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							}
						}
					}
				}
				else if ((m_board.whiteRooks >> (y * 8 + x)) & 1) {
					reVal.whiteMat += getPieceVal<EXIST>(2);
					if (!((moveAbleWhite >> (y * 8 + x)) & 1))
						continue;
					for (int num = 0; num < 4; ++num) {
						for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8; ++i) {
							if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x+i*rookMove[num].x, y + i*rookMove[num].y);
								setSpot(whiteAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
								break;
							}else if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								++reVal.whiteMoves;
								setSpot(whiteAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
								break;
							}else {
								++reVal.whiteMoves;
								setSpot(whiteAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							}
						}
					}
				}
				else if ((m_board.whiteHorse >> (y * 8 + x)) & 1) {
					reVal.whiteMat += getPieceVal<EXIST>(3);
					if (!((moveAbleWhite >> (y * 8 + x)) & 1))
						continue;
					for (unsigned num = 0; num < 8; ++num) {
						if (x + horseMove[num].x < 8 && y + horseMove[num].y < 8) {
							if (getSpot(whitePieces, x + horseMove[num].x, y + horseMove[num].y)) {
								reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x + horseMove[num].x, y + horseMove[num].y);
							}
							else {
								++reVal.whiteMoves;
								if (getSpot(blackPieces, x + horseMove[num].x, y + horseMove[num].y)) {
									reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + horseMove[num].x, y + horseMove[num].y);
								}
							}
							setSpot(whiteAttackable, x + horseMove[num].x, y + horseMove[num].y, 1);
						}
					}
				}
				else if ((m_board.whiteQueen >> (y * 8 + x)) & 1) {
					reVal.whiteMat += getPieceVal<EXIST>(4);
					if (!((moveAbleWhite >> (y * 8 + x)) & 1))
						continue;
					for (unsigned num = 0; num < 4; ++num) {//bish
						for (int i = 1; (x + (int)(i*bishMove[num].x)) < 8 && (y + (int)(i*bishMove[num].y)) < 8; ++i) {
							setSpot(whiteAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								break;
							}
							else if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								++reVal.whiteMoves;
								break;
							}
							else {
								++reVal.whiteMoves;
							}
						}//rook
						for (int i = 1; (x + (int)(i*rookMove[num].x)) < 8 && (y + (int)(i*rookMove[num].y)) < 8; ++i) {
							setSpot(whiteAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								break;
							}
							else if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								++reVal.whiteMoves;
								break;
							}
							else {
								++reVal.whiteMoves;
							}
						}
					}
				}
			}
			else {
				if ((m_board.blackPawns >> (y * 8 + x)) & 1) {
					reVal.blackMat += getPieceVal<EXIST>(6);
					if (!((moveAbleBlack >> (y * 8 + x)) & 1))
						continue;
					if (x + 1 < 8) {
						if (getSpot(whitePieces, x + 1, y + 1)) {
							reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + 1, y + 1)+1;
							++reVal.blackMoves;
						}
						else if (getSpot(blackPieces, x + 1, y + 1)) {
							reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + 1, y + 1);
						}
						setSpot(blackAttackable, x + 1, y + 1, 1);
					}
					if (x - 1 < 8) {
						if (getSpot(whitePieces, x - 1, y + 1)) {
							reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, x - 1, y + 1)+1;
							++reVal.blackMoves;
						}
						else if (getSpot(blackPieces, x - 1, y + 1)) {
							reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x - 1, y + 1);
						}
						setSpot(blackAttackable, x - 1, y + 1, 1);
					}
				}
				else if ((m_board.blackBish >> (y * 8 + x)) & 1) {
					reVal.blackMat += getPieceVal<EXIST>(7);
					if (!((moveAbleBlack >> (y * 8 + x)) & 1))
						continue;
					for (unsigned num = 0; num < 4; ++num) {
						for (int i = 1; (unsigned)(x + i*bishMove[num].x) < 8 && (unsigned)(y + i*bishMove[num].y) < 8; ++i) {
							setSpot(blackAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								break;
							}
							else if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								++reVal.blackMoves;
								break;
							}
							else {
								++reVal.blackMoves;
							}
						}
					}
				}
				else if ((m_board.blackRooks >> (y * 8 + x)) & 1) {
					reVal.blackMat += getPieceVal<EXIST>(8);
					if (!((moveAbleBlack >> (y * 8 + x)) & 1))
						continue;
					for (int num = 0; num < 4; ++num) {
						for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8; ++i) {
							setSpot(blackAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + i*rookMove[num].x, y+ i*rookMove[num].y);
								break;
							}
							else if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								++reVal.blackMoves;
								break;
							}
							else {
								++reVal.blackMoves;
							}
						}
					}
				}
				else if ((m_board.blackHorse >> (y * 8 + x)) & 1) {
					reVal.blackMat += getPieceVal<EXIST>(9);
					if (!((moveAbleBlack >> (y * 8 + x)) & 1))
						continue;

					for (unsigned num = 0; num < 8; ++num) {
						if (x + horseMove[num].x < 8 && y + horseMove[num].y < 8) {
							setSpot(blackAttackable, x + horseMove[num].x, y + horseMove[num].y, 1);
							if (getSpot(blackPieces, x + horseMove[num].x, y + horseMove[num].y)) {
								reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + horseMove[num].x, y + horseMove[num].y);
							}
							else {
								++reVal.blackMoves;
								if (getSpot(whitePieces, x + horseMove[num].x, y + horseMove[num].y)) {
									reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + horseMove[num].x, y + horseMove[num].y);
								}
							}
						}
					}
				}
				else if ((m_board.blackQueen >> (y * 8 + x)) & 1) {
					reVal.blackMat += getPieceVal<EXIST>(10);
					if (!((moveAbleBlack >> (y * 8 + x)) & 1))
						continue;
					for (unsigned num = 0; num < 4; ++num) {//bish
						for (int i = 1; (x + (int)(i*bishMove[num].x)) < 8 && (y + (int)(i*bishMove[num].y)) < 8; ++i) {
							setSpot(blackAttackable, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								break;
							}else if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
								reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + i*bishMove[num].x, y + i*bishMove[num].y);
								++reVal.blackMoves;
								break;
							}else {
								++reVal.blackMoves;
							}
						}//rook
						for (int i = 1; (x + (int)(i*rookMove[num].x)) < 8 && (y + (int)(i*rookMove[num].y)) < 8; ++i) {
							setSpot(blackAttackable, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.blackDefend += getPieceVal2<DEFEND>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								break;
							}else if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
								reVal.blackAttack += getPieceVal2<ATTACK>(m_board, x + i*rookMove[num].x, y + i*rookMove[num].y);
								++reVal.blackMoves;
								break;
							}else {
								++reVal.blackMoves;
							}
						}
					}
				}
			}
		}
	}
	//king stuff
	doKingStuff(reVal,whiteAttackable,blackAttackable);

	return reVal;
}
void ptsEvaluater::doKingStuff(getMovesPtsOutput & reVal, const uint64_t whiteAttackable, const uint64_t blackAttackable){
	//const auto fullBoard = m_board.getFullBoard();
	const auto whitePieces = m_board.getWhitePieces();
	const auto blackPieces = m_board.getBlackPieces();

	for (int num = 0; num < 8; ++num) {
		if (whitekingXpos + kingMove[num].x < 8 && whitekingYpos + kingMove[num].y < 8) {
			if (!getSpot(blackAttackable, whitekingXpos + kingMove[num].x < 8, whitekingYpos + kingMove[num].y)) {
				if (getSpot(whitePieces, whitekingXpos + kingMove[num].x, whitekingYpos + kingMove[num].y)) {
					reVal.whiteDefend += getPieceVal2<DEFEND>(m_board, whitekingXpos + kingMove[num].x, whitekingYpos + kingMove[num].y) + 2;
				}
				else {
					reVal.whiteMoves += 1;
					if (getSpot(blackPieces, whitekingXpos + kingMove[num].x, whitekingYpos + kingMove[num].y)) 
						reVal.whiteAttack += getPieceVal2<ATTACK>(m_board, whitekingXpos + kingMove[num].x, whitekingYpos + kingMove[num].y);					
				}
			}
		}else{
			reVal.whiteDefend += 2;
		}		
		if (blackKingXpos + kingMove[num].x < 8 && blackKingYpos + kingMove[num].y < 8) {
			if (!getSpot(whiteAttackable, blackKingXpos + kingMove[num].x < 8, blackKingYpos + kingMove[num].y)) {
				if (getSpot(blackPieces, blackKingXpos + kingMove[num].x, blackKingYpos + kingMove[num].y)) {
					reVal.blackDefend += getPieceVal2<DEFEND>(m_board, blackKingXpos + kingMove[num].x, blackKingYpos + kingMove[num].y) + 2;
				}
				else {
					reVal.blackDefend += 1;
					if (getSpot(whitePieces, blackKingXpos + kingMove[num].x, whitekingYpos + kingMove[num].y)) 
						reVal.blackAttack += getPieceVal2<ATTACK>(m_board, blackKingXpos + kingMove[num].x, blackKingYpos + kingMove[num].y);
				}
			}
		}else{
			reVal.blackDefend += 2;
		}
	}
}

template<>
int ptsEvaluater::checkCheck<WHITE>(){
	const unsigned kingXpos = whiteKingSpot & 7;
	const unsigned kingYpos = whiteKingSpot >> 3;
	const auto blackPieces = m_board.getWhitePieces();
	int numAttacks = 0;

	cw::vector2ui blocking = { 100,100 };//100,100 is placeholder for none
	for (int num = 0; num < 4; ++num) {
		blocking = {100,100};
		for (int i = 1; (unsigned)(kingXpos + (int)(i * bishMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * bishMove[num].y)) < 8; ++i) {
			if (getSpot(blackPieces, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					blocking = { kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y };
				else break;
			}
			else if (getSpot(m_board.blackBish, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y) || getSpot(m_board.blackQueen, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					++numAttacks;
				else {
					setSpot(moveAbleBlack, blocking.x, blocking.y, 0);
				}break;
			}
		}
		blocking = { 100,100 };
		for (int i = 1; (unsigned)(kingXpos + (int)(i * rookMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * rookMove[num].y)) < 8 ; ++i) {
			if (getSpot(blackPieces, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					blocking = { kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y };
				else break;
			}
			else if (getSpot(m_board.blackRooks, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y) || getSpot(m_board.blackQueen, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					++numAttacks;
				else {
					setSpot(moveAbleBlack, blocking.x, blocking.y, 0);
				}break;
			}
		}
	}//horsey moves
	for (int num = 0; num < 8; ++num) {
		if (kingXpos + horseMove[num].x < 8 && kingYpos + horseMove[num].y < 8) {
			if (getSpot(m_board.blackHorse, kingXpos + horseMove[num].x, kingYpos + horseMove[num].y)) {
				++numAttacks;
			}
		}
	}
	//pawns
	if (getSpot(m_board.blackPawns, kingXpos + 1, kingYpos - 1) || getSpot(m_board.blackPawns, kingXpos - 1, kingYpos - 1)) {
		++numAttacks;
	}
	return numAttacks;
}

template<>
int ptsEvaluater::checkCheck<BLACK>() {
	const unsigned kingXpos = blackKingSpot & 7;
	const unsigned kingYpos = blackKingSpot >> 3;
	const auto blackPieces = m_board.getBlackPieces();
	int numAttacks = 0;

	cw::vector2ui blocking = {100,100};
	for (int num = 0; num < 4; ++num) {
		blocking = { 100,100 };
		for (int i = 1; (unsigned)(kingXpos + (int)(i * bishMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * bishMove[num].y)) < 8; ++i) {
			if (getSpot(blackPieces, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					blocking = cw::vector2ui(kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y );
				else break;
			}
			else if (getSpot(m_board.whiteBish, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y) || getSpot(m_board.whiteQueen, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					++numAttacks;
				else {
					setSpot(moveAbleBlack, blocking.x, blocking.y, 0);
				}break;
			}
		}
		blocking = { 100,100 };
		for (int i = 1; (unsigned)(kingXpos + (int)(i * rookMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * rookMove[num].y)) < 8; ++i) {
			if (getSpot(blackPieces, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					blocking = cw::vector2ui(kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y);
				else break;
			}
			else if (getSpot(m_board.whiteRooks, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y) || getSpot(m_board.whiteQueen, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
				if (blocking == cw::vector2ui(100, 100))
					++numAttacks;
				else {
					setSpot(moveAbleBlack, blocking.x, blocking.y, 0);
				}break;
			}
		}
	}//horsey moves
	for (int num = 0; num < 8; ++num) {
		if (kingXpos + horseMove[num].x < 8 && kingYpos + horseMove[num].y < 8) {
			if (getSpot(m_board.whiteHorse, kingXpos + horseMove[num].x, kingYpos + horseMove[num].y)) {
				++numAttacks;
			}
		}
	}
	//pawns
	if (getSpot(m_board.whitePawns, kingXpos + 1, kingYpos + 1) || getSpot(m_board.whitePawns, kingXpos - 1, kingYpos + 1)) {
		++numAttacks;
	}
	return numAttacks;
}

std::pair<int, int> ptsEvaluater::checkIfCheck() {

	return std::pair<int, int>(checkCheck<BLACK>(), checkCheck<WHITE>());
}
