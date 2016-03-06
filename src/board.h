/*
 * board.h
 *
 *  Created on: Dec 21, 2015
 *      Author: echo
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "side.h"

class Piece;

const int WHITE_OFFICER_ROW = 0;
const int WHITE_PAWN_ROW = 1;
const int WHITE_ENPASSANT_ROW = 5;

const int BLACK_OFFICER_ROW = 7;
const int BLACK_PAWN_ROW = 6;
const int BLACK_ENPASSANT_ROW = 4;

class Position {
private:
	int numberPosition;
	int letterPosition;

public:

	Position() : numberPosition(0), letterPosition(0) {}
	Position(int row, int col);

	int getNumber() {return numberPosition;}
	int getLetter() {return letterPosition;}

	Position stepNorth(int steps=1);
	Position stepNorthEast(int steps=1);
	Position stepNorthWest(int steps=1);
	Position stepSouth(int steps=1);
	Position stepSouthEast(int steps=1);
	Position stepSouthWest(int steps=1);
	Position stepEast(int steps=1);
	Position stepWest(int steps=1);
};

class Board {
private:
	static const int height = 8;
	static const int width = 8;
	Piece ***board;

public:
	Board();

	void setBoard(Piece ***newBoard) {board = newBoard;}

	std::vector<Piece*> get();
	void set(std::vector<Piece*> pieces);
	void setSquare(Position pos, Piece* piece);
	void clear();

	int evaluate();

	int getHeight(){return height;}
	int getWidth(){return width;}
	bool isOutOfBounds(Position position);

	std::vector<Piece*> getPiecesBySide(Side side);
	std::vector<Piece*> getWhitePieces();
	std::vector<Piece*> getBlackPieces();
	Piece *getPieceAt(Position position);

	void capturePiece(Position position);
	void movePiece(Position from, Position to);

	void draw();
};



#endif /* BOARD_H_ */
