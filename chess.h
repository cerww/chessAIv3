#ifndef CHESS_H
#define CHESS_H
#include "app.h"
#include "chessPiece.h"
#include <unordered_map>
#include <type_traits>
#include <algorithm>
#include <utility>
#include "chessAI.h"
#include <thread>
#include "vectors.h"
enum class turn{WHITE,BLACK};
class chess:public app{
	public:
		chess();
		~chess();
		void run();
	private:
		void m_drawMenu();
		void movePiece(chessPiece*,const chessPiece*,bool);
		void m_newGame();
		void m_drawGame();
		chessPiece* selectedPiece;
		chessPiece* mouseOverPiece;
		int turns;
		
		std::vector<chessPiece*> m_pieces;
		chessBoard m_board;
		void m_iHateTheKing();
		pieceColor check = pieceColor::NONE;
		sf::Vector2i whiteKingSpot;
		sf::Vector2i blackKingSpot;
		chessPiece* whiteKing;
		chessPiece* blackKing;
		void m_checkWin();
		template<class T>
		void pawnPromotion();
		chessPiece* pawnAtEnd = nullptr; 
		pieceColor won = pieceColor::NONE;
		bool useAI = 1;
		
};
#endif

