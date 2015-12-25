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

enum Side {WHITE, BLACK};

class Piece {
protected:
	Side side;
	short value;
	Position position;

public:
	Piece(Side side, int value);
	virtual ~Piece(){}

	Side getSide() {return side;}
	short getValue() {return value;}

	std::vector<Position> getLegalManhattanMoves(Board *board);
	std::vector<Position> getLegalDiagonalMoves(Board *board);

	virtual std::vector<Position> getLegalMoves(Board *board) = 0;
	virtual void move(Position to);
};

class Pawn: public Piece {
private:
	bool enPassant;
public:
	Pawn(Side side, int value);
	std::vector<Position> getLegalMoves(Board *board);
	void move(Board *board, Position to);
	bool canEnPassant() { return enPassant; }
};

class Rook: public Piece {
public:
	Rook(Side side, int value) : Piece(side, value) {}
	std::vector<Position> getLegalMoves(Board *board);
};

class Knight: public Piece {
public:
	Knight(Side side, int value) : Piece(side, value) {}
	std::vector<Position> getLegalMoves(Board *board);
};

class Bishop: public Piece {
public:
	Bishop(Side side, int value) : Piece(side, value) {}
	std::vector<Position> getLegalMoves(Board *board);
};

class Queen: public Piece {
public:
	Queen(Side side, int value) : Piece(side, value) {}
	std::vector<Position> getLegalMoves(Board *board);
};

class King: public Piece {
public:
	King(Side side, int value) : Piece(side, value) {}
	std::vector<Position> getLegalMoves(Board *board);
};

#endif /* PIECES_H_ */
