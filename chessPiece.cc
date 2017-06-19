#include "chessPiece.h"
#include "vectors2.h"
//chessPiece::chessPiece(pieceColor color,int lx,int ly){}
chessPiece::~chessPiece(){}
chessPiece::chessPiece(){}

void horse::genMoveSpots(chessBoard& board){
	static constexpr cw::vector2i horseMove[8] = { { 1,2 },{ -1,2 },{ 1,-2 },{ -1,-2 },{ 2,1 },{ 2,-1 },{ -2,1 },{ -2,-1 } };
	moveSpots.clear();
	for(int num = 0;num<8;++num){
		if((unsigned)(bx+horseMove[num].x)<8&&(unsigned)(by+horseMove[num].y)<8){
			if(board.board[bx+horseMove[num].x][by+horseMove[num].y].onTile->color!=color)		
				moveSpots.emplace_back(bx+horseMove[num].x,by+horseMove[num].y);
			board.board[bx+horseMove[num].x][by+horseMove[num].y].k[this]=something({},{});
			
		}
	}
}
void rook::genMoveSpots(chessBoard& board){
	moveSpots.clear();
	std::vector<sf::Vector2i> path(1,sf::Vector2i(bx,by));
	std::vector<chessPiece*> blocking;
	for(int x = bx+1;x<8;++x){
		board.board[x][by].k[this]=something(blocking,path);
		if(board.board[x][by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
		}else if(board.board[x][by].onTile->color==color){
			blocking.push_back(board.board[x][by].onTile.get());
		}else{	
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
			blocking.push_back(board.board[x][by].onTile.get());
		}path.emplace_back(x,by);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int x = bx-1;x>=0;--x){
		board.board[x][by].k[this]=something(blocking,path);
		if(board.board[x][by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
		}else if(board.board[x][by].onTile->color==color){//same color
			blocking.push_back(board.board[x][by].onTile.get());
		}else{
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
			blocking.push_back(board.board[x][by].onTile.get());
		}path.emplace_back(x,by);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int y = by+1;y<8;++y){
		board.board[bx][y].k[this]=something(blocking,path);
		if(board.board[bx][y].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
		}else if(board.board[bx][y].onTile->color==color){
			blocking.push_back(board.board[bx][y].onTile.get());
		}else{			
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
			blocking.push_back(board.board[bx][y].onTile.get());
		}path.emplace_back(bx,y);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int y = by-1;y>=0;--y){
		board.board[bx][y].k[this]=something(blocking,path);
		if(board.board[bx][y].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
		}else if(board.board[bx][y].onTile->color==color){
			blocking.push_back(board.board[bx][y].onTile.get());
		}else{
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
			blocking.push_back(board.board[bx][y].onTile.get());
		}path.emplace_back(bx,y);
	}
}
void bishop::genMoveSpots(chessBoard& board){
	moveSpots.clear();
	//+x +y
	std::vector<sf::Vector2i> path;
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	std::vector<chessPiece*> blocking;
	for(int c = 1;c+bx<8&&c+by<8;++c){
		board.board[bx+c][by+c].k[this] = something(blocking,path);	
		if(board.board[c+bx][c+by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(c+bx,c+by);
		}
		else if(board.board[c+bx][c+by].onTile->color==color)
			blocking.push_back(board.board[bx+c][by+c].onTile.get());
		else if(board.board[c+bx][c+by].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(c+bx,c+by);	
			blocking.push_back(board.board[bx+c][by+c].onTile.get());
		}path.emplace_back(bx+c,by+c);
	}
	//-x -y
	blocking.clear();
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	for(int c = 1;bx-c>=0&&by-c>=0;++c){
		board.board[bx-c][by-c].k[this] = something(blocking,path);	
		if(board.board[bx-c][by-c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by-c);
		}
		else if(board.board[bx-c][by-c].onTile->color==color)
			blocking.push_back(board.board[bx-c][by-c].onTile.get());
		else if(board.board[bx-c][by-c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by-c);
			blocking.push_back(board.board[bx-c][by-c].onTile.get());
		}path.emplace_back(bx-c,by-c);
	}
	//+x -y
	blocking.clear();
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	for(int c = 1;bx+c<8&&by-c>=0;++c){
		board.board[bx+c][by-c].k[this] = something(blocking,path);	
		if(board.board[bx+c][by-c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx+c,by-c);
		}
		else if(board.board[bx+c][by-c].onTile->color==color)
			blocking.push_back(board.board[bx+c][by-c].onTile.get());
		else if(board.board[bx+c][by-c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx+c,by-c);
			blocking.push_back(board.board[bx+c][by-c].onTile.get());
		}path.emplace_back(bx+c,by-c);
	}
	//-x +y
	blocking.clear();
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	for(int c = 1;bx-c>=0&&by+c<8;++c){
		board.board[bx-c][by+c].k[this] = something(blocking,path);	
		if(board.board[bx-c][by+c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by+c);
		}
		else if(board.board[bx-c][by+c].onTile->color==color)
			blocking.push_back(board.board[bx-c][by+c].onTile.get());
		else if(board.board[bx-c][by+c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by+c);
			blocking.push_back(board.board[bx-c][by+c].onTile.get());
		}path.emplace_back(bx-c,by+c);
	}
}
void pawn::genMoveSpots(chessBoard& board){
	//moveableSpots=std::vector<std::vector<char> >(8,std::vector<char>(8,0));
	moveSpots.clear();
	if(color==pieceColor::BLACK){
		for(int x = 1;x<3-movedBefore;++x){
			if(board.board[bx][by+x].onTile->color==pieceColor::NONE)
				moveSpots.emplace_back(bx,by+x);
			else break;
		}
		if(bx!=7)
			if(board.board[bx+1].at(by+1).onTile->color==pieceColor::WHITE){
				moveSpots.emplace_back(bx+1,(by+1));
				board.board[bx+1].at(by+1).k[this] = something();
			}
		if(bx!=0)
			if(board.board[bx-1].at(by+1).onTile->color==pieceColor::WHITE){
				moveSpots.emplace_back(bx-1,by+1);
				board.board[bx-1].at(by+1).k[this] = something();
			}
	}
	else {
		for(int x = 1;x<3-movedBefore;++x){
			if(board.board[bx][by-x].onTile->color==pieceColor::NONE)
				moveSpots.emplace_back(bx,by-x);
			else break;
		}
		if(bx!=7)
			if(board.board.at(bx+1).at(by-1).onTile->color==pieceColor::BLACK){
				moveSpots.emplace_back(bx+1,by-1);
				board.board[bx+1].at(by-1).k[this] = something();
			}
		if(bx!=0)
			if(board.board.at(bx-1).at(by-1).onTile->color==pieceColor::BLACK){
				moveSpots.emplace_back(bx-1,by-1);
				board.board[bx-1].at(by-1).k[this] = something();
			}
	}
}
void queen::genMoveSpots(chessBoard& board){
	moveSpots.clear();
	std::vector<sf::Vector2i> path;
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	std::vector<chessPiece*> blocking;
	for(int x = bx+1;x<8;++x){
		board.board[x][by].k[this]=something(blocking,path);
		if(board.board[x][by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
		}else if(board.board[x][by].onTile->color==color){
			blocking.push_back(board.board[x][by].onTile.get());
		}else{	
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
			blocking.push_back(board.board[x][by].onTile.get());
		}path.emplace_back(x,by);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int x = bx-1;x>=0;--x){
		board.board[x][by].k[this]=something(blocking,path);
		if(board.board[x][by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
		}else if(board.board[x][by].onTile->color==color){//same color
			blocking.push_back(board.board[x][by].onTile.get());
		}else{
			if(!blocking.size())
				moveSpots.emplace_back(x,by);
			blocking.push_back(board.board[x][by].onTile.get());
		}path.emplace_back(x,by);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int y = by+1;y<8;++y){
		board.board[bx][y].k[this]=something(blocking,path);
		if(board.board[bx][y].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
		}else if(board.board[bx][y].onTile->color==color){
			blocking.push_back(board.board[bx][y].onTile.get());
		}else{			
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
			blocking.push_back(board.board[bx][y].onTile.get());
		}path.emplace_back(bx,y);
	}
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int y = by-1;y>=0;--y){
		board.board[bx][y].k[this]=something(blocking,path);
		if(board.board[bx][y].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
		}else if(board.board[bx][y].onTile->color==color){
			blocking.push_back(board.board[bx][y].onTile.get());
		}else{
			if(!blocking.size())
				moveSpots.emplace_back(bx,y);
			blocking.push_back(board.board[bx][y].onTile.get());
		}path.emplace_back(bx,y);
	}
	//bishop part-------------------
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	blocking.clear();
	for(int c = 1;c+bx<8&&c+by<8;++c){
		board.board[bx+c][by+c].k[this] = something(blocking,path);	
		if(board.board[c+bx][c+by].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(c+bx,c+by);
		}
		else if(board.board[c+bx][c+by].onTile->color==color)
			blocking.push_back(board.board[bx+c][by+c].onTile.get());
		else if(board.board[c+bx][c+by].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(c+bx,c+by);	
			blocking.push_back(board.board[bx+c][by+c].onTile.get());
		}path.emplace_back(bx+c,by+c);
	}
	//-x -y
	blocking.clear();
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	for(int c = 1;bx-c>=0&&by-c>=0;++c){
		board.board[bx-c][by-c].k[this] = something(blocking,path);	
		if(board.board[bx-c][by-c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by-c);
		}
		else if(board.board[bx-c][by-c].onTile->color==color)
			blocking.push_back(board.board[bx-c][by-c].onTile.get());
		else if(board.board[bx-c][by-c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by-c);
			blocking.push_back(board.board[bx-c][by-c].onTile.get());
		}path.emplace_back(bx-c,by-c);
	}
	//+x -y
	blocking.clear();
	path.clear();
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	for(int c = 1;bx+c<8&&by-c>=0;++c){
		board.board[bx+c][by-c].k[this] = something(blocking,path);	
		if(board.board[bx+c][by-c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx+c,by-c);
		}
		else if(board.board[bx+c][by-c].onTile->color==color)
			blocking.push_back(board.board[bx+c][by-c].onTile.get());
		else if(board.board[bx+c][by-c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx+c,by-c);
			blocking.push_back(board.board[bx+c][by-c].onTile.get());
		}path.emplace_back(bx+c,by-c);
	}
	//-x +y
	blocking.clear();
	path.clear();
	for(int c = 1;bx-c>=0&&by+c<8;++c){
		board.board[bx-c][by+c].k[this] = something(blocking,path);	
		if(board.board[bx-c][by+c].onTile->color==pieceColor::NONE){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by+c);
		}
		else if(board.board[bx-c][by+c].onTile->color==color)
			blocking.push_back(board.board[bx-c][by+c].onTile.get());
		else if(board.board[bx-c][by+c].onTile->color!=color){
			if(!blocking.size())
				moveSpots.emplace_back(bx-c,by+c);
			blocking.push_back(board.board[bx-c][by+c].onTile.get());
		}path.emplace_back(bx-c,by+c);
	}
}
void king::genMoveSpots(chessBoard& board){
	moveSpots.clear();
	//std::vector<sf::Vector2i> path;// = std::vector<sf::Vector2i>;
	std::vector<sf::Vector2i> path;
	path = std::vector<sf::Vector2i>(1,sf::Vector2i(bx,by));
	std::vector<chessPiece*> blocking;
	if(bx!=7){
		if(by!=7){
			board.board[bx+1][by+1].k[this]=something(blocking,path);
			if(board.board[bx+1][by+1].onTile->color!=color)
				moveSpots.emplace_back(bx+1,by+1);
		}
		board.board[bx+1][by+0].k[this]=something(blocking,path);
		if(board.board[bx+1][by+0].onTile->color!=color)
			moveSpots.emplace_back(bx+1,by  );
		if(by!=0){
			board.board[bx+1][by-1].k[this]=something(blocking,path);
			if(board.board[bx+1][by-1].onTile->color!=color)
				moveSpots.emplace_back(bx+1,by-1);
		}
	}
	if(bx!=0){
		if(by!=7){
			board.board[bx-1][by+1].k[this]=something(blocking,path);
			if(board.board[bx-1][by+1].onTile->color!=color)
				moveSpots.emplace_back(bx-1,by+1);
		}
		board.board[bx-1][by-0].k[this]=something(blocking,path);
		if(board.board[bx-1][by+0].onTile->color!=color)
			moveSpots.emplace_back(bx-1,by+0);
		if(by!=0){
			board.board[bx-1][by-1].k[this]=something(blocking,path);
			if(board.board[bx-1][by-1].onTile->color!=color)
				moveSpots.emplace_back(bx-1,by-1);
		}
	}if(by!=7){
		board.board[bx  ][by+1].k[this]=something(blocking,path);
		if(board.board[bx  ][by+1].onTile->color!=color)
			moveSpots.emplace_back(bx  ,by+1);
	}
	if(by!=0){
		board.board[bx  ][by-1].k[this]=something(blocking,path);
		if(board.board[bx  ][by-1].onTile->color!=color)
			moveSpots.emplace_back(bx  ,by-1);
	}//king special move thingy
	if(color==pieceColor::WHITE){
		if(bx == 4&&by ==7){
			if(board.board[5][7].onTile->color==pieceColor::NONE&&board.board[6][7].onTile->color==pieceColor::NONE&&board.board[7][7].onTile->piece==pieceName::ROOK){
				moveSpots.emplace_back(6,7);
			}if(board.board[3][7].onTile->color==pieceColor::NONE&&board.board[2][7].onTile->color==pieceColor::NONE&&board.board[1][7].onTile->color==pieceColor::NONE&&board.board[0][7].onTile->piece==pieceName::ROOK){
				moveSpots.emplace_back(2,7);
			}
		}
	}
	else if(color==pieceColor::BLACK){
		if(bx == 4&&by ==0){
			if(board.board[5][0].onTile->color==pieceColor::NONE&&board.board[6][0].onTile->color==pieceColor::NONE&&board.board[7][0].onTile->piece==pieceName::ROOK){
				moveSpots.emplace_back(6,0);
			}if(board.board[3][0].onTile->color==pieceColor::NONE&&board.board[2][0].onTile->color==pieceColor::NONE&&board.board[1][0].onTile->color==pieceColor::NONE&&board.board[0][0].onTile->piece==pieceName::ROOK){
				moveSpots.emplace_back(2,0);
			}
		}
	}
}
void noPiece::genMoveSpots(chessBoard&){}
