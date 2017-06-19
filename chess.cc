#include "chess.h"
#include "vectors2.h"
#include "ai.h"
#include <bitset>
#define print std::cout<<
chess::chess(){
	newWindow("main",1000,810);
}
template<class t1,class t2>
bool sameClass(t2 in){
	//print std::boolalpha;
	return std::is_same<t1,t2>::value;
}
void chess::movePiece(chessPiece* a,const chessPiece* b,bool spm=false){
	int x = b->bx;
	int y = b->by;
	a->movedBefore= 1;
	m_board.board[b->bx][b->by].onTile=m_board.board[a->bx][a->by].onTile;
	m_board.board[a->bx][a->by].onTile=std::make_shared<noPiece>(a->bx,a->by);
	if(abs(a->bx-x)==2&&a->piece==pieceName::KING){
		movePiece(m_board.board[a->bx-x>0?0:7][a->by].onTile.get(),m_board.board[a->bx-x>0?3:5][a->by].onTile.get(),true);
		//--turns;//inefficientcy is nice
		//yay no more inefficiantcy
	}
	a->bx = x;
	a->by = y;
	selectedPiece=nullptr;
	if(a->piece==pieceName::PAWN&&a->by==(a->color==pieceColor::WHITE?0:7)){
		pawnAtEnd = a;
		return;
	}
	if(spm) return;
	m_pieces.clear();
	for(unsigned x = 0;x<8;++x){
		for(unsigned y = 0;y<8;++y){
			m_board.board[x][y].k.clear();
		}
	}
	for(unsigned x = 0;x<8;++x){
		for(unsigned y = 0;y<8;++y){
			if(m_board.board[x][y].onTile->color!=pieceColor::NONE){
				m_pieces.push_back(m_board.board[x][y].onTile.get());
				m_board.board[x][y].onTile->genMoveSpots(m_board);
			}
		}
	}m_iHateTheKing();
	++turns;
}
void chess::m_newGame(){
	turns = 0;
	//m_board.resize(8,std::vector<std::shared_ptr<chessPiece> >(8));
	for(int x = 0;x<8;++x){
		m_board.board[x][1].onTile=std::make_shared<pawn>(x,1,pieceColor::BLACK);
		m_board.board[x][6].onTile=std::make_shared<pawn>(x,6,pieceColor::WHITE);
		for(int y = 2;y<6;++y){
			m_board.board[x][y].onTile=std::make_shared<noPiece>(x,y);
		}
	}
	m_board.board[0][0].onTile=std::make_shared<rook>  (0,0,pieceColor::BLACK);
	m_board.board[1][0].onTile=std::make_shared<horse> (1,0,pieceColor::BLACK);
	m_board.board[2][0].onTile=std::make_shared<bishop>(2,0,pieceColor::BLACK);
	m_board.board[3][0].onTile=std::make_shared<queen> (3,0,pieceColor::BLACK);
	m_board.board[4][0].onTile=std::make_shared<king>  (4,0,pieceColor::BLACK);
	m_board.board[5][0].onTile=std::make_shared<bishop>(5,0,pieceColor::BLACK);
	m_board.board[6][0].onTile=std::make_shared<horse> (6,0,pieceColor::BLACK);
	m_board.board[7][0].onTile=std::make_shared<rook>  (7,0,pieceColor::BLACK);
	
	m_board.board[0][7].onTile=std::make_shared<rook>  (0,7,pieceColor::WHITE);
	m_board.board[1][7].onTile=std::make_shared<horse> (1,7,pieceColor::WHITE);
	m_board.board[2][7].onTile=std::make_shared<bishop>(2,7,pieceColor::WHITE);
	m_board.board[3][7].onTile=std::make_shared<queen> (3,7,pieceColor::WHITE);
	m_board.board[4][7].onTile=std::make_shared<king>  (4,7,pieceColor::WHITE);
	m_board.board[5][7].onTile=std::make_shared<bishop>(5,7,pieceColor::WHITE);
	m_board.board[6][7].onTile=std::make_shared<horse> (6,7,pieceColor::WHITE);
	m_board.board[7][7].onTile=std::make_shared<rook>  (7,7,pieceColor::WHITE);
	
	m_pieces.clear();
	for(unsigned x = 0;x<8;++x){
		for(unsigned y = 0;y<8;++y){
			if(m_board.board[x][y].onTile->color!=pieceColor::NONE){
				m_pieces.push_back(m_board.board[x][y].onTile.get());
			}
		}
	}
	whiteKing = m_board.board[4][7].onTile.get();
	blackKing = m_board.board[4][0].onTile.get();
	selectedPiece = nullptr;
	mouseOverPiece = nullptr;
}
void chess::run(){
	m_newGame();
	//if(sameClass<int>(1))std::cout<<"abcaa"<<std::endl;
	for(int x = 0;x<8;++x){ 
		for(int y = 0;y<8;++y){
			//std::cout<<x<<y<<std::endl;
			m_board.board[x][y].onTile->genMoveSpots(m_board);
		}
	}std::thread AIb;
	std::pair<cw::vector2<int8_t>,cw::vector2<int8_t> > AImove;
	while(isRunning()){
		update();
		windows["main"]->clear(sf::Color::White);

		if(getMouseCoords("main").x<804&&getMouseCoords("main").y<804&&getMouseCoords("main").y>5&&getMouseCoords("main").x>5)
			mouseOverPiece = m_board.board[(getMouseCoords("main").x-5)/100][(getMouseCoords("main").y-5)/100].onTile.get();
		else mouseOverPiece=nullptr;
		if(getMouseClick("main",mouseButton::LEFT)){
		//if(0){
			//bool breakOut=0;
			if(getMouseCoords("main").x<804&&getMouseCoords("main").y<804&&getMouseCoords("main").y>5&&getMouseCoords("main").x>5){
				if((selectedPiece)&&(turns%2!=(int)mouseOverPiece->color)){
					//if((*selectedPiece->getMoveSpots())[mouseOverPiece->bx][mouseOverPiece->by]){
					if(std::find(selectedPiece->getMoveSpots2()->begin(),selectedPiece->getMoveSpots2()->end(),sf::Vector2i(mouseOverPiece->bx,mouseOverPiece->by))!=selectedPiece->getMoveSpots2()->end()){
						movePiece(selectedPiece,mouseOverPiece);
					}else{std::cout<<"can't move there"<<std::endl;}
				}else
				if(((mouseOverPiece)&&(turns%2==(int)mouseOverPiece->color))){
				//if(mouseOverPiece){
					selectedPiece=mouseOverPiece;
					selectedPiece =selectedPiece->color== pieceColor::NONE?nullptr:selectedPiece;
					if(useAI){
						selectedPiece = selectedPiece->color==pieceColor::BLACK?nullptr:selectedPiece;
					}
				}
			}
		}
		if(getMouseClick("main",mouseButton::RIGHT)){
			for(int x = 0;x<8;++x){
				for(int y = 0;y<8;++y){
					//std::cout<<x<<y<<std::endl;
					if(m_board.board[x][y].onTile->color==pieceColor::NONE)
						continue;
					//m_board.board[x][y].onTile->genMoveSpots(m_board);
				}
			}	
		}
		if(pawnAtEnd!=nullptr){
			if(getMouseClick("main",mouseButton::LEFT)&&getMouseCoords("main").x>805&&getMouseCoords("main").x<1000&&getMouseCoords("main").y>=200&&getMouseCoords("main").y<401){
				if(getMouseCoords("main").y>=200&&getMouseCoords("main").y<251){
					//rook
					pawnPromotion<rook>();
				}if(getMouseCoords("main").y>=251&&getMouseCoords("main").y<301){
					//queen
					pawnPromotion<queen>();
				}if(getMouseCoords("main").y>=300&&getMouseCoords("main").y<351){
					//horse
					pawnPromotion<horse>();
				}if(getMouseCoords("main").y>=351&&getMouseCoords("main").y<401){
					//bishop
					pawnPromotion<bishop>();
				}
			}		
		}
		
		if(turns%2==1&& !AI::done&&useAI&& !AIb.joinable()){
			chessB boardForAI;
			bitBoard BFORAI (0,0,0,0,0,0,0,0,0,0,0,0);
			for(int x = 0;x<8;++x){
				for(int y = 0;y<8;++y){
					//boardForAI.b[x][y] = Cpiece(m_board.board[x][y].onTile->piece,m_board.board[x][y].onTile->color);
					if(m_board.board[x][y].onTile->piece==pieceName::NONE) continue;
					if(m_board.board[x][y].onTile->piece==pieceName::PAWN){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whitePawns,x,y,1);
						}else{
							setSpot(BFORAI.blackPawns,x,y,1);
						}
					}else if(m_board.board[x][y].onTile->piece==pieceName::BISHOP){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whiteBish,x,y,1);
						}else{
							setSpot(BFORAI.blackBish,x,y,1);
						}
					}
					else if(m_board.board[x][y].onTile->piece==pieceName::QUEEN){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whiteQueen,x,y,1);
						}else{
							setSpot(BFORAI.blackQueen,x,y,1);
						}
					}
					else if(m_board.board[x][y].onTile->piece==pieceName::KING){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whiteKing,x,y,1);
						}else{
							setSpot(BFORAI.blackKing,x,y,1);
						}
					}
					else if(m_board.board[x][y].onTile->piece==pieceName::ROOK){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whiteRooks,x,y,1);
						}else{
							setSpot(BFORAI.blackRooks,x,y,1);
						}
					}
					else if(m_board.board[x][y].onTile->piece==pieceName::HORSE){
						if(m_board.board[x][y].onTile->color==pieceColor::WHITE){
							setSpot(BFORAI.whiteHorse,x,y,1);
						}else{
							setSpot(BFORAI.blackHorse,x,y,1);
						}
					}
				}
			}
			//std::cout<<std::bitset<64>(BFORAI.getFullBoard()).to_string()<<std::endl;
			AIb = std::thread(AIrun,BFORAI,&AImove);
			//chessAI::done = 1;
		}
		if(AI::done&&useAI){
			AIb.join();
			AI::done = 0;
			movePiece(m_board.board[AImove.first.x][AImove.first.y].onTile.get(),m_board.board[AImove.second.x][AImove.second.y].onTile.get());
			std::cout<<(int)AImove.first.x<<" "<<(int)AImove.first.y<<std::endl<<(int)AImove.second.x<<" "<<(int)AImove.second.y<<std::endl;
			if(pawnAtEnd!=nullptr){
				pawnPromotion<queen>();
			}
		}
		m_drawGame();
		
		windows["main"]->display();
	}
}
void chess::m_drawMenu(){

}
void chess::m_checkWin(){
	if(check == pieceColor::NONE) return;
	for(auto piece:m_pieces)
		if(piece->color==check&&piece->getMoveSpots2()->size())
			return;
	std::string a = (int)check==0?"black":"white";
	won = (int)check==0?pieceColor::BLACK:pieceColor::WHITE;
	std::cout<<a<<" wins"<<std::endl;
}
void chess::m_drawGame(){
	std::vector<sf::Vertex> verts(m_pieces.size()*4);
	sf::Sprite board(*getTexture("workPls.png"));
	
	for(unsigned int x=0;x<m_pieces.size();++x){
	//for(unsigned x= m_pieces.size()-1;x!=-1;--x){
		verts[4*x+0]=sf::Vertex(sf::Vector2f(5+m_pieces[x]->bx*100,5+m_pieces[x]->by*100),m_pieces[x]->color==pieceColor::BLACK?sf::Color(120,120,120,255):sf::Color(255,255,255,255),sf::Vector2f(0,0)+m_pieces[x]->textCoords);
		verts[4*x+1]=sf::Vertex(sf::Vector2f(105+m_pieces[x]->bx*100,5+m_pieces[x]->by*100),m_pieces[x]->color==pieceColor::BLACK?sf::Color(120,120,120,255):sf::Color(255,255,255,255),sf::Vector2f(100,0)+m_pieces[x]->textCoords);
		verts[4*x+2]=sf::Vertex(sf::Vector2f(105+m_pieces[x]->bx*100,105+m_pieces[x]->by*100),m_pieces[x]->color==pieceColor::BLACK?sf::Color(120,120,120,255):sf::Color(255,255,255,255),sf::Vector2f(100,100)+m_pieces[x]->textCoords);
		verts[4*x+3]=sf::Vertex(sf::Vector2f(5+m_pieces[x]->bx*100,105+m_pieces[x]->by*100),m_pieces[x]->color==pieceColor::BLACK?sf::Color(120,120,120,255):sf::Color(255,255,255,255),sf::Vector2f(0,100)+m_pieces[x]->textCoords);
	}
	
	windows["main"]->draw(board);
	if(mouseOverPiece!=nullptr){
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(100,100));
		r.setFillColor(sf::Color(50,200,50,208));
		r.setPosition(5+mouseOverPiece->bx*100,5+mouseOverPiece->by*100);
		windows["main"]->draw(r);
	}
	if(selectedPiece!=nullptr&&selectedPiece!=mouseOverPiece){
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(100,100));
		r.setFillColor(sf::Color(50,50,200,208));
		r.setPosition(5+selectedPiece->bx*100,5+selectedPiece->by*100);
		windows["main"]->draw(r);
	}
	if(selectedPiece!=nullptr){
		for(const auto &x:*(selectedPiece->getMoveSpots2())){
			sf::RectangleShape r;
			r.setSize(sf::Vector2f(100,100));
			r.setFillColor(sf::Color(200,50,50,208));
			r.setPosition(5+x.x*100,5+x.y*100);
			windows["main"]->draw(r);
		}
	}
	if(check!=pieceColor::NONE&&won==pieceColor::NONE){
		std::string a = (int)check==0?"white":"black";
		sf::Text text(a+"check",*getFont("coolvetica rg.ttf"),30);
		text.setPosition(sf::Vector2f(815.0f,0.0f));
		text.setStyle(sf::Text::Regular);
		text.setFillColor(sf::Color::Black);
		windows["main"]->draw(text);
	}
	if(won!=pieceColor::NONE){
		std::string a = (int)check==0?"black":"white";
		sf::Text text(a+" wins",*getFont("coolvetica rg.ttf"),30);
		text.setPosition(sf::Vector2f(815.0f,0.0f));
		text.setStyle(sf::Text::Regular);
		text.setFillColor(sf::Color::Black);
		windows["main"]->draw(text);
	}
	if(pawnAtEnd!=nullptr){
		for(int x = 0;x<4;++x){
			sf::Text text(((std::vector<std::string>){"rook","queen","horse","bishop"})[x],*getFont("coolvetica rg.ttf"),30);
			text.setPosition(sf::Vector2f(815.0f,200.0f+50*x));
			text.setStyle(sf::Text::Regular);
			text.setFillColor(sf::Color::Black);
			windows["main"]->draw(text);
		}	
	}
	windows["main"]->draw(&verts[0],m_pieces.size()*4,sf::Quads,getTexture("abca.png"));
}
void chess::m_iHateTheKing(){
	check = pieceColor::NONE;
	std::vector<std::vector<char> > spots=std::vector<std::vector<char> >(8,std::vector<char>(8,0));
	std::vector<std::vector<char> > whiteMoveSpots=std::vector<std::vector<char> >(8,std::vector<char>(8,0));
	std::vector<std::vector<char> > blackMoveSpots=std::vector<std::vector<char> >(8,std::vector<char>(8,0));
	//print " a"<<std::endl;
	for(const auto& x:m_pieces){
		for(const sf::Vector2i& y:*(x->getMoveSpots2())){
			if(x->color==pieceColor::WHITE){
				//std::cout<<"abc"<<std::endl;
				whiteMoveSpots[y.x][y.y]=1;
				//m_board.board[blackKingSpot.x][blackKingSpot.y].onTile->removeMoveSpot(y);
				if(x->piece!=pieceName::PAWN)
					blackKing->removeMoveSpot(y);
				else{
					blackKing->removeMoveSpot({x->bx-1,x->by-1});
					blackKing->removeMoveSpot({x->bx+1,x->by-1});
				}
			}
			else if(x->color==pieceColor::BLACK){
				blackMoveSpots[y.x][y.y]=1;
				//m_board.board[whiteKingSpot.x][whiteKingSpot.y].onTile->removeMoveSpot(y);
				if(x->piece!=pieceName::PAWN)
					whiteKing->removeMoveSpot(y);
				else{
					whiteKing->removeMoveSpot({x->bx-1,x->by+1});
					whiteKing->removeMoveSpot({x->bx+1,x->by+1});
				}
			}
		}
	}
	for(auto& x:cp(*(whiteKing->getMoveSpots2()))){
		for(auto& y:m_board.board[x.x][x.y].k){
			if(y.first->color==pieceColor::BLACK&&y.second.blocking.size()==0
			&&y.first->piece!=pieceName::PAWN){
				whiteKing->removeMoveSpot(x);
			}
		}
	}
	for(auto& x:cp(*(blackKing->getMoveSpots2()))){
		for(auto& y:m_board.board[x.x][x.y].k){
			if(y.first->color==pieceColor::WHITE&&y.second.blocking.size()==0
			&&y.first->piece!=pieceName::PAWN){
				blackKing->removeMoveSpot(x);
			}
		}
	}
	//return;
	//white
	int numa=0;
	for(const auto& x:m_board.board[whiteKing->bx][whiteKing->by].k){
		//iterate through all pieces that can go to the white's king spot if no other pieces exist
		if(x.first->color==pieceColor::BLACK){
			//check if white is checked
			if(!x.second.blocking.size()){
				check = pieceColor::WHITE;
				for(auto& y:x.second.path){
					spots[y.x][y.y]=1;
				}spots[x.first->bx][x.first->by]=1;
				++numa;
			}
			if(x.second.blocking.size()==1){
				if(x.second.blocking[0]->color==pieceColor::WHITE)
					x.second.blocking[0]->restrictMoveSpots(x.second.path);
				//if only 1 pieces is blocking another piece
				//from eatting the king,that piece cant move
			}
		}
	}if(numa>1){
		for(auto& piece:m_pieces){
			if(piece->color==pieceColor::WHITE&&piece!=whiteKing){
				piece->killSpots();
			}
		}
	}
	if(numa==1){
		for(auto &whitePiece:m_pieces){
			//if(whitePiece->color==pieceColor::WHITE&&whitePiece->piece!=pieceName::KING){
			if(whitePiece->color==pieceColor::WHITE&&whitePiece!=whiteKing){
				auto c = *whitePiece->getMoveSpots2();
				for(auto pathy:c){
					if(!spots[pathy.x][pathy.y]){
						whitePiece->removeMoveSpot(pathy);
					}
				}
			}
		}
	}
	if(check == pieceColor::WHITE){
		std::cout<<"white check"<<std::endl;
	}//
	for(int spot = ((*whiteKing->getMoveSpots2())).size()-1;spot>=0;--spot){//spots around the king
		for(const auto& are:m_board.board[(*whiteKing->getMoveSpots2())[spot].x][(*whiteKing->getMoveSpots2())[spot].y].k){
			if(are.first->color==pieceColor::BLACK&&
			   are.second.blocking.size()==1&& 
			   are.second.blocking[0]==whiteKing){
				whiteKing->removeMoveSpot((*whiteKing->getMoveSpots2())[spot]);
			}
		}
	}
	std::vector<sf::Vector2i> spotsToRemove;
	for(auto& spot:*(whiteKing->getMoveSpots2())){
		for(auto& i:m_board.board[spot.x][spot.y].k){
			if(i.first->color==pieceColor::BLACK){
				if(i.second.blocking.size()==0){
					spotsToRemove.push_back(spot);
				}
			}
		}
		if(spot.x-1>=0&&spot.x-1<8&&spot.y-1>=0&&spot.y-1<8&&
		   m_board.board[spot.x-1][spot.y-1].onTile->piece==pieceName::PAWN&&
		   m_board.board[spot.x-1][spot.y-1].onTile->color==pieceColor::BLACK){
			  spotsToRemove.push_back(spot);
		}
		if(spot.x+1>=0&&spot.x+1<8&&spot.y-1>=0&&spot.y-1<8&&
		   m_board.board[spot.x+1][spot.y-1].onTile->piece==pieceName::PAWN&&
		   m_board.board[spot.x+1][spot.y-1].onTile->color==pieceColor::BLACK){
			  spotsToRemove.push_back(spot);
		}
	}
	for(const auto& i:spotsToRemove){
		whiteKing->removeMoveSpot(i);
	}
	//black
	spots=std::vector<std::vector<char> >(8,std::vector<char>(8,0));
	numa=0;
	for(const auto& x:m_board.board[blackKing->bx][blackKing->by].k){		
		//iterate through all pieces that can go to the white's king spot if no other pieces exist
		if(x.first->color==pieceColor::WHITE){
			//check if white is checked
			if(!x.second.blocking.size()){
				check = pieceColor::BLACK;
				for(auto& y:x.second.path){
					spots[y.x][y.y]=1;
				}spots[x.first->bx][x.first->by]=1;
				++numa;
			}
			if(x.second.blocking.size()==1){
				//if only 1 pieces is blocking another piece
				//from eatting the king,that piece cant move
				if(x.second.blocking[0]->color==pieceColor::BLACK)
					x.second.blocking[0]->restrictMoveSpots(x.second.path);
			}
		}
	}if(numa>1){
		for(auto& piece:m_pieces){
			if(piece->color==pieceColor::BLACK&&piece!=blackKing){
				piece->killSpots();
			}
		}
	}
	if(numa==1){
		for(auto &whitePiece:m_pieces){
			//if(whitePiece->color==pieceColor::WHITE&&whitePiece->piece!=pieceName::KING){
			if(whitePiece->color==pieceColor::BLACK&&whitePiece!=blackKing){
				auto c = *whitePiece->getMoveSpots2();
				for(auto pathy:c){
					if(!spots[pathy.x][pathy.y]){
						whitePiece->removeMoveSpot(pathy);
					}
				}
			}
		}
	}
	for(int spot = (*blackKing->getMoveSpots2()).size()-1;spot>=0;--spot){
		for(auto& are:m_board.board[(*blackKing->getMoveSpots2())[spot].x][(*blackKing->getMoveSpots2())[spot].y].k){
			if(are.first->color==pieceColor::WHITE&&are.second.blocking.size()==1&& are.second.blocking[0]==blackKing){
				blackKing->removeMoveSpot((*blackKing->getMoveSpots2())[spot]);
			}
		}
	}
	spotsToRemove.clear();
	for(auto& spot:*(blackKing->getMoveSpots2())){
		for(auto& i:m_board.board[spot.x][spot.y].k){
			if(i.first->color==pieceColor::WHITE){
				if(i.second.blocking.size()==0){
					spotsToRemove.push_back(spot);
				}
			}
		}
		if(spot.x-1>=0&&spot.x-1<8&&spot.y+1<8&&
		   m_board.board[spot.x-1][spot.y+1].onTile->piece==pieceName::PAWN&&
		   m_board.board[spot.x-1][spot.y+1].onTile->color==pieceColor::WHITE){
			  spotsToRemove.push_back(spot);
		}
		if(spot.x+1>=0&&spot.x+1<8&&spot.y+1<8&&
		   m_board.board[spot.x+1][spot.y+1].onTile->piece==pieceName::PAWN&&
		   m_board.board[spot.x+1][spot.y+1].onTile->color==pieceColor::WHITE){
			  spotsToRemove.push_back(spot);
		}
	}
	//for(
	for(const auto& i:spotsToRemove){
		whiteKing->removeMoveSpot(i);
	}
	if(check == pieceColor::BLACK){
		std::cout<<"blackCheck"<<std::endl;
	}m_checkWin();
}

template<typename T>
void chess::pawnPromotion(){
	for(unsigned x = 0;x<8;++x){
		for(unsigned y = 0;y<8;++y){
			m_board.board[x][y].k.clear();
		}
	}
	m_board.board[pawnAtEnd->bx][pawnAtEnd->by].onTile = std::make_shared<T>(pawnAtEnd->bx,pawnAtEnd->by,pawnAtEnd->color);
	pawnAtEnd = nullptr;
	selectedPiece=nullptr;
	m_pieces.clear();
	
	for(unsigned x = 0;x<8;++x){
		for(unsigned y = 0;y<8;++y){
			if(m_board.board[x][y].onTile->color!=pieceColor::NONE){
				m_pieces.push_back(m_board.board[x][y].onTile.get());
				m_board.board[x][y].onTile->genMoveSpots(m_board);
			}
		}
	}m_iHateTheKing();
	++turns;
}
chess::~chess(){
	//delete tx;
}



