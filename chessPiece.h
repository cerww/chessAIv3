#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include "vecFuncs.h"
enum class pieceColor:char{WHITE,BLACK,NONE};
enum class pieceName:char{PAWN,ROOK,BISHOP,QUEEN,KING,HORSE,NONE};
class chessPiece;
struct chessBoard;//{public:chessPiece* a;};
class chessTile;

struct something{
	//chessPiece* toThisTile;
	something(std::vector<chessPiece*> p,std::vector<sf::Vector2i> a):path(a),blocking(p){}
	something(){}
	std::vector<sf::Vector2i> path;
	std::vector<chessPiece*> blocking;
};
struct chessTile{
	std::shared_ptr<chessPiece> onTile;
	std::unordered_map<chessPiece*,something> k;	
};
struct chessBoard{
	std::array<std::array<chessTile,8>,8 > board;
	//std::array<sf::Vector2f,2> kingSpots;
};
class chessPiece{//:public sf::Drawable{
public:
	chessPiece(int lx,int ly,pieceColor c=pieceColor::NONE,sf::Vector2f v=sf::Vector2f(0,0),pieceName pn=pieceName::NONE):bx(lx),by(ly),color(c),textCoords(v),piece(pn){};
	chessPiece();
	virtual ~chessPiece();
	int bx;
	int by;
	bool movedBefore = 0;
	pieceColor color;// = pieceColor::NONE;
	const sf::Vector2f textCoords;//=sf::Vector2f(100,0);
	pieceName piece;// = pieceName::NONE;
	//virtual void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&)=0;
	virtual void genMoveSpots(chessBoard&)=0;
	//void genMoveSpots(const std::vector<std::vector<chessPiece> >&);
	std::vector<std::vector<char> >* getMoveSpots(){return &moveableSpots;};
	std::vector<sf::Vector2i>* getMoveSpots2(){return &moveSpots;};
	void killSpots(){moveSpots.clear();};
	void removeMoveSpot(const sf::Vector2i& a){removeIfInVec(&moveSpots,a);};
	void addMoveSpot(const sf::Vector2i& a){moveSpots.push_back(a);};
	void restrictMoveSpots(const std::vector<sf::Vector2i>& a){
		moveSpots = moveSpots & a;
	};
protected:
	std::vector<std::vector<char> > moveableSpots;
	std::vector<sf::Vector2i> moveSpots;
};
class horse:public chessPiece{
public:
	horse(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(0,0),pieceName::HORSE){};
	horse(){};
	const sf::Vector2f textCoords=sf::Vector2f(0,0);
	pieceName piece = pieceName::HORSE;
	virtual ~horse(){};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class pawn:public chessPiece{
public:
	pawn(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(100,0),pieceName::PAWN){};//(pieceColor,int,int):chessPiece(lx,ly,c){};
	pawn(){};
	virtual ~pawn(){};
	const sf::Vector2f textCoords=sf::Vector2f(100,0);
	pieceName piece = pieceName::PAWN;
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class queen:public chessPiece{
public:
	queen(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(200,0),pieceName::QUEEN){};//(pieceColor,int,int):chessPiece(lx,ly,c){};
	queen(){};
	const sf::Vector2f textCoords=sf::Vector2f(200,0);
	pieceName piece = pieceName::QUEEN;
	~queen(){};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class king:public chessPiece{
public:
	king(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(300,0),pieceName::KING){};//(pieceColor,int,int):chessPiece(lx,ly,c){};
	virtual ~king(){};
	const sf::Vector2f textCoords=sf::Vector2f(300,0);
	pieceName piece = pieceName::KING;
	king(){};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class bishop:public chessPiece{
public:
	bishop(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(400,0),pieceName::BISHOP){};//(pieceColor,int,int):chessPiece(lx,ly,c){};
	bishop(){};
	const sf::Vector2f textCoords=sf::Vector2f(400,0);
	pieceName piece = pieceName::BISHOP;
	virtual ~bishop(){};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class rook:public chessPiece{
public:
	rook(int x,int y,pieceColor c):chessPiece(x,y,c,sf::Vector2f(500,0),pieceName::ROOK){};//(pieceColor,int,int):chessPiece(lx,ly,c){};
	rook(){};
	const sf::Vector2f textCoords=sf::Vector2f(500,0);
	pieceName piece = pieceName::ROOK;
	virtual ~rook(){};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};
class noPiece:public chessPiece{
public:
	noPiece(int x,int y):chessPiece(x,y,pieceColor::NONE,sf::Vector2f(600,0)){};
	noPiece(){};
	const sf::Vector2f textCoords=sf::Vector2f(600,0);
	pieceName piece = pieceName::NONE;
	virtual ~noPiece(){}//{std::cout<<<<std::endl;};
	//void genMoveSpots(const std::vector<std::vector<std::shared_ptr<chessPiece> > >&);
	void genMoveSpots(chessBoard&);
};

#endif

