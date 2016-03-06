/*
 * pieces.h
 *
 *  Created on: Dec 21, 2015
 *      Author: echo
 */

#ifndef PIECES_H_
#define PIECES_H_

#include <vector>
#include "board.h"
#include "side.h"

class Piece {
protected:
	Side side;
	short value;
	Position position;
	char c;

public:
	Piece(Side side, int value, Position position);
	virtual ~Piece(){}

	Side getSide() {return side;}
	short getValue() {return value;}

	int getRow() {return position.getNumber(); }
	int getCol() {return position.getLetter(); }
	Position getPosition() {return position; }
	void setPosition(Position position) { this->position = position; }

	std::vector<Position> getLegalManhattanMoves(Board *board);
	std::vector<Position> getLegalDiagonalMoves(Board *board);

	virtual std::vector<Position> getLegalMoves(Board *board) = 0;
	virtual void move(Board *board, Position to);

	char toChar() { return c; }
};

class Pawn: public Piece {
private:
	bool enPassant;
public:
	Pawn(Side side, int value, Position position) : Piece(side, value, position) { enPassant = false; c = side == WHITE ? 'P' : 'p'; }
	std::vector<Position> getLegalMoves(Board *board);
	void move(Board *board, Position to);
	bool canEnPassant() { return enPassant; }
};

class Rook: public Piece {
public:
	Rook(Side side, int value, Position position) : Piece(side, value, position) { c = side == WHITE ? 'R' : 'r'; }
	std::vector<Position> getLegalMoves(Board *board);
};

class Knight: public Piece {
public:
	Knight(Side side, int value, Position position) : Piece(side, value, position) { c = side == WHITE ? 'N' : 'n'; }
	std::vector<Position> getLegalMoves(Board *board);
};

class Bishop: public Piece {
public:
	Bishop(Side side, int value, Position position) : Piece(side, value, position) { c = side == WHITE ? 'B' : 'b'; }
	std::vector<Position> getLegalMoves(Board *board);
};

class Queen: public Piece {
public:
	Queen(Side side, int value, Position position) : Piece(side, value, position) { c = side == WHITE ? 'Q' : 'q'; }
	std::vector<Position> getLegalMoves(Board *board);
};

class King: public Piece {
public:
	King(Side side, int value, Position position) : Piece(side, value, position) {
		c = side == WHITE ? 'K' : 'k';
	}
	std::vector<Position> getLegalMoves(Board *board);
};

#endif /* PIECES_H_ */
