/*
 * board.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: echo
 */

#include <cstdlib>
#include "pieces.h"

Position::Position(int x, int y) {
	letterPosition = x;
	numberPosition = y;
}

Position Position::stepNorth(int steps) {
	return Position(letterPosition, numberPosition+steps);
}

Position Position::stepSouth(int steps) {
	return Position(letterPosition, numberPosition-steps);
}

Position Position::stepEast(int steps) {
	return Position(letterPosition+steps, numberPosition);
}

Position Position::stepWest(int steps) {
	return Position(letterPosition-steps, numberPosition);
}

Position Position::stepNorthEast(int steps) {
	return Position(letterPosition+steps, numberPosition+steps);
}

Position Position::stepNorthWest(int steps) {
	return Position(letterPosition-steps, numberPosition+steps);
}

Position Position::stepSouthEast(int steps) {
	return Position(letterPosition+steps, numberPosition-steps);
}

Position Position::stepSouthWest(int steps) {
	return Position(letterPosition-steps, numberPosition-steps);
}

Board::Board() {

	// Initialize white pieces
	board[0][0] = new Rook(WHITE, 5);
	board[0][1] = new Knight(WHITE, 3);
	board[0][2] = new Bishop(WHITE, 3);
	board[0][3] = new Queen(WHITE, 9);
	board[0][4] = new King(WHITE, 0);
	board[0][5] = new Bishop(WHITE, 3);
	board[0][6] = new Knight(WHITE, 3);
	board[0][7] = new Rook(WHITE, 5);

	board[1][0] = new Pawn(WHITE, 1);
	board[1][1] = new Pawn(WHITE, 1);
	board[1][2] = new Pawn(WHITE, 1);
	board[1][3] = new Pawn(WHITE, 1);
	board[1][4] = new Pawn(WHITE, 1);
	board[1][5] = new Pawn(WHITE, 1);
	board[1][6] = new Pawn(WHITE, 1);
	board[1][7] = new Pawn(WHITE, 1);

	// Initialize black pieces
	board[7][0] = new Rook(BLACK, 5);
	board[7][1] = new Knight(BLACK, 3);
	board[7][2] = new Bishop(BLACK, 3);
	board[7][3] = new Queen(BLACK, 9);
	board[7][4] = new King(BLACK, 0);
	board[7][5] = new Bishop(BLACK, 3);
	board[7][6] = new Knight(BLACK, 3);
	board[7][7] = new Rook(BLACK, 5);

	board[6][0] = new Pawn(BLACK, 1);
	board[6][1] = new Pawn(BLACK, 1);
	board[6][2] = new Pawn(BLACK, 1);
	board[6][3] = new Pawn(BLACK, 1);
	board[6][4] = new Pawn(BLACK, 1);
	board[6][5] = new Pawn(BLACK, 1);
	board[6][6] = new Pawn(BLACK, 1);
	board[6][7] = new Pawn(BLACK, 1);
}

int Board::evaluate() {
	int whitePoints = 0;
	int blackPoints = 0;

	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			Piece *piece = board[i][j];
			if (piece != NULL) {
				if (piece->getSide() == WHITE) {
					whitePoints += piece->getValue();
				} else {
					blackPoints += piece->getValue();
				}
			}
		}
	}

	return whitePoints - blackPoints;
}

bool Board::isOutOfBounds(Position position) {
	return position.getNumber() < height && position.getLetter() < width &&
		   position.getNumber() >= 0     && position.getLetter() >= 0;
}

Piece *Board::getPieceAt(Position position) {
	return board[position.getNumber()][position.getLetter()];
}


void Board::capturePiece(Position position) {
	Piece *piece = getPieceAt(position);
	delete piece;
	board[position.getNumber()][position.getLetter()] = NULL;
}

void Board::movePiece(Position from, Position to) {
	Piece *moved = board[from.getNumber()][from.getLetter()];
	board[from.getNumber()][from.getLetter()] = NULL;
	board[to.getNumber()][to.getLetter()] = moved;
}

