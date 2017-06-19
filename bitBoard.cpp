#include "bitBoard.h"
#include <thread>
#include <utility>
bool getSpot(const uint64_t& b, const uint8_t x, const uint8_t y) {
	return (b >> (y * 8 + x)) & 1;
}

uint64_t getPieceVal(const int p) {
	static constexpr int vals[12] = { 10,30,50,30,90,1000000,10,30,50,30,90,1000000 };
	return vals[p];
}

bitBoard moveSpot(bitBoard b, const int8_t x1, const int8_t y1, const int8_t x2, const int8_t y2) {
	for (unsigned i = 0; i < 12; ++i) {
		if (getSpot(b.allPieces[i], x1, y1)) {
			if (i == 0 && y2 == 0) {
				setSpot(b.whitePawns, x1, y1, 0);
				setSpot(b.whiteQueen, x2, y2, 1);
				break;
			}
			else if (i == 6 && y2 == 7) {
				setSpot(b.blackPawns, x1, y1, 0);
				setSpot(b.blackQueen, x2, y2, 1);
				break;
			}
			else {
				setSpot(b.allPieces[i], x2, y2, 1);
				setSpot(b.allPieces[i], x1, y1, 0);
			}
		}
		else {
			setSpot(b.allPieces[i], x2, y2, 0);
		}
	}return b;
}

template<>
std::vector<bitBoard> getBoards<color::WHITE>(const bitBoard &b) {
	static const cw::vector2i bishMove[4] = { {1,1},{-1,1},{-1,-1},{1,-1} };
	static const cw::vector2i rookMove[4] = { {1,0},{-1,0},{0,1},{0,-1} };

	std::vector<bitBoard> returnVal;
	returnVal.reserve(50);
	const auto fullBoard = b.getFullBoard();
	const auto blackPieces = b.getBlackPieces();
	const auto whitePieces = b.getWhitePieces();
	for (int y = 0; y < 8; ++y) {
		if (!((whitePieces >> (y * 8)) & (255))) continue;
		for (int x = 0; x < 8; ++x) {
			if (!((whitePieces >> (y * 8 + x)) & 1)) continue;
			if ((b.whitePawns >> (y * 8 + x)) & 1) {
				for (unsigned i = 1; i < 2 + (unsigned)(y == 6); ++i) {
					if (!getSpot(fullBoard, x, y - i)) {
						auto temp = b;
						setSpot(temp.whitePawns, x, y, 0);
						if (y - i != 0)
							setSpot(temp.whitePawns, x, y - i, 1);
						else
							setSpot(temp.whiteQueen, x, y - i, 1);
						returnVal.push_back(temp);
						
					}
					else break;
				}
				if (getSpot(blackPieces, x + 1, y - 1)) {
					returnVal.push_back(moveSpot(b, x, y, x + 1, y - 1));
				}
				if (getSpot(blackPieces, x - 1, y - 1)) {
					returnVal.push_back(moveSpot(b, x, y, x- 1, y - 1));
				}
			}
			else if ((b.whiteBish >> (y * 8 + x)) & 1) {
				for (unsigned num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + i*bishMove[num].x)< 8 && (unsigned)(y + i*bishMove[num].y) < 8; ++i) {
						if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							break;
						}
						else if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*bishMove[num].x, y + i*bishMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.whiteBish, x, y, 0);
							setSpot(temp.whiteBish, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}
			}
			else if ((b.whiteRooks >> (y * 8 +x)) & 1) {
				for (int num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8;++i) {
						if (getSpot(whitePieces, x+i*rookMove[num].x, y+i*rookMove[num].y)) {
							break;
						}
						else if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*rookMove[num].x, y + i*rookMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.whiteRooks, x, y, 0);
							setSpot(temp.whiteRooks, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}				
			}			
			else if ((b.whiteHorse >> (y * 8 + x)) & 1) {
				if (x + 2 < 8) {
					if (y + 1 < 8 && !getSpot(whitePieces, x + 2, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 2, y + 1));
					}
					if (y - 1 >= 0 && !getSpot(whitePieces, x + 2, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 2, y - 1));
					}
				}
				if (x - 2 >= 0) {
					if (y + 1 < 8 && !getSpot(whitePieces, x - 2, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x - 2, y + 1));
					}
					if (y - 1 >= 0 && !getSpot(whitePieces, x - 2, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x - 2, y - 1));
					}
				}
				if (y + 2 < 8) {
					if (x + 1 < 8 && !getSpot(whitePieces, x + 1, y + 2)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y + 2));
					}
					if (x - 1 >= 0 && !getSpot(whitePieces, x - 1, y + 2)) {
						returnVal.push_back(moveSpot(b, x, y, x - 1, y + 2));
					}
				}
				if (y - 2 >= 0) {
					if (x + 1 < 8 && !getSpot(whitePieces, x + 1, y - 2)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y - 2));
					}
					if (x - 1 >= 0 && !getSpot(whitePieces, x - 1, y - 2)) {
						returnVal.push_back(moveSpot(b, x, y, x - 1, y - 2));
					}
				}
			}
			else if ((b.whiteQueen >> (y * 8 + x)) & 1) {
				for (unsigned num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + (int)(i*bishMove[num].x))< 8 && (unsigned)(y + (int)(i*bishMove[num].y)) < 8; ++i) {
						if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							break;
						}
						else if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*bishMove[num].x, y + i*bishMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.whiteQueen, x, y, 0);
							setSpot(temp.whiteQueen, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
					for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8; ++i) {
						if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							break;
						}
						else if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*rookMove[num].x, y + i*rookMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.whiteQueen, x, y, 0);
							setSpot(temp.whiteQueen, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}
			}
			else if ((b.whiteKing >> (y * 8 + x)) & 1) {
				if (x + 1 < 8) {
					if (y + 1 < 8 && !getSpot(whitePieces, x + 1, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y + 1));
					}
					if (!getSpot(whitePieces, x + 1, y))
						returnVal.push_back(moveSpot(b, x, y, x + 1, y));
					if (y - 1 >= 0 && !getSpot(whitePieces, x + 1, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y - 1));
					}
				}
				if (x - 1 >= 0) {
					if (y + 1 < 8 && !getSpot(whitePieces, x - 1, y + 1))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y + 1));

					if (!getSpot(whitePieces, x - 1, y))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y));

					if (y - 1 >= 0 && !getSpot(whitePieces, x - 1, y - 1))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y - 1));

				}
				if (y + 1 < 8 && !getSpot(whitePieces, x, y + 1)) {
					returnVal.push_back(moveSpot(b, x, y, x, y + 1));
				}
				if (y - 1 >= 0 && !getSpot(whitePieces, x, y - 1))
					returnVal.push_back(moveSpot(b, x, y, x, y - 1));
			}
		}
	}
	return pruneWhite(std::move(returnVal));
}

template<>
std::vector<bitBoard> getBoards<color::BLACK>(const bitBoard &b) {
	static const cw::vector2i bishMove[4] = { { 1,1 },{ -1,1 },{ -1,-1 },{ 1,-1 } };
	static const cw::vector2i rookMove[4] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };

	std::vector<bitBoard> returnVal;
	returnVal.reserve(50);
	const auto fullBoard = b.getFullBoard();
	const auto blackPieces = b.getBlackPieces();
	const auto whitePieces = b.getWhitePieces();
	for (int y = 0; y < 8; ++y) {
		if (!((blackPieces >> (y * 8)) & (255))) continue;
		for (int x = 0; x < 8; ++x) {
			if (!((blackPieces >> (y * 8 + x)) & 1)) continue;
			if ((b.blackPawns >> (y * 8 + x)) & 1) {
				for (unsigned i = 1; i < 2 + (unsigned)(y == 1); ++i) {
					if (!getSpot(fullBoard, x, y + i)) {
						auto temp = b;
						setSpot(temp.blackPawns, x, y, 0);
						if (y + i != 7)
							setSpot(temp.blackPawns, x, y + i, 1);
						else
							setSpot(temp.blackQueen, x, y + i, 1);
						returnVal.push_back(std::move(temp));
						
					}
					else break;
				}
				if (getSpot(whitePieces, x + 1, y + 1) && x + 1 < 8) 
					returnVal.push_back(moveSpot(b, x, y, x + 1, y + 1));
				if (getSpot(whitePieces, x - 1, y + 1) && x - 1 >= 0) 
					returnVal.push_back(moveSpot(b, x, y, x - 1, y + 1));
			}
			else if ((b.blackBish >> (y * 8 + x)) & 1) {
				for (unsigned num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + i*bishMove[num].x)< 8 && (unsigned)(y + i*bishMove[num].y) < 8; ++i) {
						if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							break;
						}
						else if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*bishMove[num].x, y + i*bishMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.blackBish, x, y, 0);
							setSpot(temp.blackBish, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}				
			}
			else if ((b.blackRooks >> (y * 8 + x)) & 1) {
				for (int num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8; ++i) {
						if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							break;
						}
						else if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*rookMove[num].x, y + i*rookMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.blackRooks, x, y, 0);
							setSpot(temp.blackRooks, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}				
			}
			else if ((b.blackHorse >> (y * 8 + x)) & 1) {
				if (x + 2 < 8) {
					if (y + 1 < 8 && !getSpot(blackPieces, x + 2, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 2, y + 1));
					}
					if (y - 1 >= 0 && !getSpot(blackPieces, x + 2, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 2, y - 1));
					}
				}
				if (x - 2 >= 0) {
					if (y + 1 < 8 && !getSpot(blackPieces, x - 2, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x - 2, y + 1));
					}
					if (y - 1 >= 0 && !getSpot(blackPieces, x - 2, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x - 2, y - 1));
					}
				}
				if (y + 2 < 8) {
					if (x + 1 < 8 && !getSpot(blackPieces, x + 1, y + 2)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y + 2));
					}
					if (x - 1 >= 0 && !getSpot(blackPieces, x - 1, y + 2)) {
						returnVal.push_back(moveSpot(b, x, y, x - 1, y + 2));
					}
				}
				if (y - 2 >= 0) {
					if (x + 1 < 8 && !getSpot(blackPieces, x + 1, y - 2)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y - 2));
					}
					if (x - 1 >= 0 && !getSpot(blackPieces, x - 1, y - 2)) {
						returnVal.push_back(moveSpot(b, x, y, x - 1, y - 2));
					}
				}
			}
			else if ((b.blackQueen >> (y * 8 + x)) & 1) {
				for (unsigned num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + (int)(i*bishMove[num].x))< 8 && (unsigned)(y + (int)(i*bishMove[num].y)) < 8; ++i) {
						if (getSpot(blackPieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							break;
						}
						else if (getSpot(whitePieces, x + i*bishMove[num].x, y + i*bishMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*bishMove[num].x, y + i*bishMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.blackQueen, x, y, 0);
							setSpot(temp.blackQueen, x + i*bishMove[num].x, y + i*bishMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
					//}
					//for (unsigned num = 0; num < 4; ++num) {
					for (int i = 1; (unsigned)(x + (int)(i*rookMove[num].x)) < 8 && (unsigned)(y + (int)(i*rookMove[num].y)) < 8; ++i) {
						if (getSpot(blackPieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							break;
						}
						else if (getSpot(whitePieces, x + i*rookMove[num].x, y + i*rookMove[num].y)) {
							returnVal.push_back(moveSpot(b, x, y, x + i*rookMove[num].x, y + i*rookMove[num].y));
							break;
						}
						else {
							bitBoard temp = b;
							setSpot(temp.blackQueen, x, y, 0);
							setSpot(temp.blackQueen, x + i*rookMove[num].x, y + i*rookMove[num].y, 1);
							returnVal.push_back(temp);
						}
					}
				}
			}
			else if ((b.blackKing >> (y * 8 + x)) & 1) {
				if (x + 1 < 8) {
					if (y + 1 < 8 && !getSpot(blackPieces, x + 1, y + 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y + 1));
					}
					if (!getSpot(blackPieces, x + 1, y))
						returnVal.push_back(moveSpot(b, x, y, x + 1, y));
					if (y - 1 >= 0 && !getSpot(blackPieces, x + 1, y - 1)) {
						returnVal.push_back(moveSpot(b, x, y, x + 1, y - 1));
					}
				}
				if (x - 1 >= 0) {
					if (y + 1 < 8 && !getSpot(blackPieces, x - 1, y + 1))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y + 1));

					if (!getSpot(blackPieces, x - 1, y))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y));

					if (y - 1 >= 0 && !getSpot(blackPieces, x - 1, y - 1))
						returnVal.push_back(moveSpot(b, x, y, x - 1, y - 1));

				}
				if (y + 1 < 8 && !getSpot(blackPieces, x, y + 1))
					returnVal.push_back(moveSpot(b, x, y, x, y + 1));

				if (y - 1 >= 0 && !getSpot(blackPieces, x, y - 1))
					returnVal.push_back(moveSpot(b, x, y, x, y - 1));
			}
		}
	}
	return pruneBlack(std::move(returnVal));
}

uint64_t setPts2(const bitBoard & b) {
    //++bitBoard::setptsNum;
    uint64_t re = 0;
    const auto fullBoard = b.getFullBoard();
    const auto blackP = b.getBlackPieces();
    //const auto whiteP = b.getWhitePieces();

    for (unsigned qwe = 0; qwe < 64; ++qwe) {
        if (!((fullBoard >> qwe) & 1)) 
            continue;

        for (unsigned i = ((blackP >> qwe) & 1) * 6; i < 12; ++i) {
            if ((b.allPieces[i] >> qwe) & 1) {
                if (i < 6)
                    re += (getPieceVal(i));//white
                else
                    re += getPieceVal(i) << 32;
                break;
            }
        }
    }
    return re;
}

std::vector<bitBoard> pruneBlack(std::vector<bitBoard>&& boards) {

	std::vector<bitBoard> re;
	re.reserve(std::max((size_t)1,boards.size()));
	for (auto&& board : boards) {
		//check if that board is worth doing
		//const auto newBoards = getBoards<color::WHITE>(board);
		const auto blackPieces = board.getBlackPieces();
		bool add = true;
		const unsigned tempCuzLogIsSlow = (unsigned)log2(board.blackKing);
		unsigned kingXpos = tempCuzLogIsSlow & 7;
		unsigned kingYpos = tempCuzLogIsSlow >> 3;
		//bish-like moves
		//*
		for (int num = 0; num < 4&&add; ++num) {
			for (int i = 1; (unsigned)(kingXpos + (int)(i * bishMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * bishMove[num].y)) < 8 && add; ++i) {
				if (getSpot(blackPieces, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
					break;
				}
				else if (getSpot(board.whiteBish, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y) || getSpot(board.whiteQueen, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
					add = false;
					break;
				}
			}
			for (int i = 1; (unsigned)(kingXpos + (int)(i * rookMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * rookMove[num].y)) < 8 && add; ++i) {
				if (getSpot(blackPieces, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
					break;
				}
				else if (getSpot(board.whiteRooks, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y) || getSpot(board.whiteQueen, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
					add = false;
					break;
				}
			}
		}
		//horsey moves
		for (int num = 0; num < 8 && add; ++num) {
			if (kingXpos + horseMove[num].x < 8 && kingYpos + horseMove[num].y < 8) {
				if (getSpot(board.whiteHorse, kingXpos + horseMove[num].x, kingYpos + horseMove[num].y)){
					add = false;
					break;
				}
			}
		}
		//pawns
		if (getSpot(board.whitePawns, kingXpos + 1, kingYpos + 1) || getSpot(board.whitePawns, kingXpos - 1, kingYpos + 1)) {
			add = false;
		}		
		if (add) {
			re.push_back(std::move(board));
		}
	}return re;
}


std::vector<bitBoard> pruneWhite(std::vector<bitBoard>&& boards) {

	std::vector<bitBoard> re;
	re.reserve(std::max((size_t)1,boards.size()));
	for (auto&& board : boards) {
		//check if that board is worth doing
		//const auto newBoards = getBoards<color::WHITE>(board);
		const auto blackPieces = board.getWhitePieces();//xd too lazy to change name
		bool add = true;
		const unsigned tempCuzLogIsSlow = log2(board.whiteKing);
		unsigned kingXpos = tempCuzLogIsSlow & 7;
		unsigned kingYpos = tempCuzLogIsSlow >>3;

		for (int num = 0; num < 4 && add; ++num) {
			for (int i = 1; (unsigned)(kingXpos + (int)(i * bishMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * bishMove[num].y)) < 8 && add; ++i) {
				if (getSpot(blackPieces, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
					break;
				}
				else if (getSpot(board.blackBish, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y) || getSpot(board.blackQueen, kingXpos + i* bishMove[num].x, kingYpos + i* bishMove[num].y)) {
					add = false;
					break;
				}
			}
			for (int i = 1; (unsigned)(kingXpos + (int)(i * rookMove[num].x)) < 8 && (unsigned)(kingYpos + (int)(i * rookMove[num].y)) < 8 && add; ++i) {
				if (getSpot(blackPieces, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
					break;
				}
				else if (getSpot(board.blackRooks, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y) || getSpot(board.blackQueen, kingXpos + i* rookMove[num].x, kingYpos + i* rookMove[num].y)) {
					add = false;
					break;
				}
			}
		}
		
		//horsey moves
		for (int num = 0; num < 8 && add; ++num) {
			if (kingXpos + horseMove[num].x < 8 && kingYpos + horseMove[num].y < 8) {
				if (getSpot(board.blackHorse, kingXpos + horseMove[num].x, kingYpos + horseMove[num].y)){
					add = false;
					break;
				}
			}
		}
		//pawns
		if (getSpot(board.blackPawns, kingXpos + 1, kingYpos - 1) || getSpot(board.blackPawns, kingXpos - 1, kingYpos - 1)) {
			add = false;
		}
		
		
		if (add) {
			re.push_back(std::move(board));
		}
	}return re;
}



