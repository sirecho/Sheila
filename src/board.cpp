/*
 * board.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: echo
 */

#include <cstdlib>
#include <iostream>
#include "pieces.h"

Position::Position(int row, int col) {
	numberPosition = row;
	letterPosition = col;
}

Position Position::stepNorth(int steps) {
	return Position(numberPosition+steps, letterPosition);
}

Position Position::stepSouth(int steps) {
	return Position(numberPosition-steps, letterPosition);
}

Position Position::stepEast(int steps) {
	return Position(numberPosition, letterPosition+steps);
}

Position Position::stepWest(int steps) {
	return Position(numberPosition, letterPosition-steps);
}

Position Position::stepNorthEast(int steps) {
	return Position(numberPosition+steps, letterPosition+steps);
}

Position Position::stepNorthWest(int steps) {
	return Position(numberPosition+steps, letterPosition-steps);
}

Position Position::stepSouthEast(int steps) {
	return Position(numberPosition-steps, letterPosition+steps);
}

Position Position::stepSouthWest(int steps) {
	return Position(numberPosition-steps, letterPosition-steps);
}

Board::Board() {

	// Allocate memory for the board
	board = new Piece**[height];
	for (int i=0; i<width; i++)
		board[i] = new Piece*[width];


	// Initialize white pieces
	board[0][0] = new Rook(WHITE, 5, Position(0,0));
	board[0][1] = new Knight(WHITE, 3, Position(0,1));
	board[0][2] = new Bishop(WHITE, 3, Position(0,2));
	board[0][3] = new Queen(WHITE, 9, Position(0,3));
	board[0][4] = new King(WHITE, 0, Position(0,4));
	board[0][5] = new Bishop(WHITE, 3, Position(0,5));
	board[0][6] = new Knight(WHITE, 3, Position(0,6));
	board[0][7] = new Rook(WHITE, 5, Position(0,7));

	board[1][0] = new Pawn(WHITE, 1, Position(1,0));
	board[1][1] = new Pawn(WHITE, 1, Position(1,1));
	board[1][2] = new Pawn(WHITE, 1, Position(1,2));
	board[1][3] = new Pawn(WHITE, 1, Position(1,3));
	board[1][4] = new Pawn(WHITE, 1, Position(1,4));
	board[1][5] = new Pawn(WHITE, 1, Position(1,5));
	board[1][6] = new Pawn(WHITE, 1, Position(1,6));
	board[1][7] = new Pawn(WHITE, 1, Position(1,7));

	// Initialize black pieces
	board[7][0] = new Rook(BLACK, 5, Position(7,0));
	board[7][1] = new Knight(BLACK, 3, Position(7,1));
	board[7][2] = new Bishop(BLACK, 3, Position(7,2));
	board[7][3] = new Queen(BLACK, 9, Position(7,3));
	board[7][4] = new King(BLACK, 0, Position(7,4));
	board[7][5] = new Bishop(BLACK, 3, Position(7,5));
	board[7][6] = new Knight(BLACK, 3, Position(7,6));
	board[7][7] = new Rook(BLACK, 5, Position(7,7));

	board[6][0] = new Pawn(BLACK, 1, Position(6,0));
	board[6][1] = new Pawn(BLACK, 1, Position(6,1));
	board[6][2] = new Pawn(BLACK, 1, Position(6,2));
	board[6][3] = new Pawn(BLACK, 1, Position(6,3));
	board[6][4] = new Pawn(BLACK, 1, Position(6,4));
	board[6][5] = new Pawn(BLACK, 1, Position(6,5));
	board[6][6] = new Pawn(BLACK, 1, Position(6,6));
	board[6][7] = new Pawn(BLACK, 1, Position(6,7));
}

void Board::clear() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j] = NULL;
		}
	}
}

std::vector<Piece*> Board::get() {
	std::vector<Piece*> pieces;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] != NULL)
				pieces.push_back(board[i][j]);
		}
	}

	return pieces;
}

void Board::set(std::vector<Piece*> pieces) {
	for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		Piece *p = *it;
		board[p->getRow()][p->getCol()] = p;
	}
}

void Board::setSquare(Position pos, Piece* piece) {
	board[pos.getNumber()][pos.getLetter()] = piece;
}

int Board::evaluate() {
	int whitePiecePoints = 0;
	int blackPiecePoints = 0;
	int whiteSquarePoints = 0;
	int blackSquarePoints = 0;


	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			Piece *piece = board[i][j];
			if (piece != NULL) {
				if (piece->getSide() == WHITE) {
					whitePiecePoints += piece->getValue();
				} else {
					blackPiecePoints += piece->getValue();
				}
			}
		}
	}

	return whitePiecePoints - blackPiecePoints;
}

bool Board::isOutOfBounds(Position position) {
	bool a = position.getNumber() < height;
	bool b = position.getLetter() < width;
	bool c = position.getNumber() >= 0;
	bool d = position.getLetter() >= 0;
	return !( a && b && c && d );
}

std::vector<Piece*> Board::getPiecesBySide(Side side) {

	std::vector<Piece*> pieces;
	for (int i=0; i<height; i++) {
			for (int j=0; j<width; j++) {
				Piece *p = board[i][j];
				if (p != NULL && p->getSide() == side)
					pieces.push_back(board[i][j]);
			}
	}

	return pieces;
}

std::vector<Piece*> Board::getWhitePieces() {
	return getPiecesBySide(WHITE);
}

std::vector<Piece*> Board::getBlackPieces() {
	return getPiecesBySide(BLACK);
}

Piece *Board::getPieceAt(Position position) {
	if (!isOutOfBounds(position))
		return board[position.getNumber()][position.getLetter()];

	return NULL;
}


void Board::capturePiece(Position position) {
	Piece *piece = getPieceAt(position);
	board[position.getNumber()][position.getLetter()] = NULL;
}

void Board::movePiece(Position from, Position to) {
	Piece *moved = board[from.getNumber()][from.getLetter()];
	board[from.getNumber()][from.getLetter()] = NULL;
	board[to.getNumber()][to.getLetter()] = moved;
}

void Board::draw() {
	std::cout << "  A B C D E F G H" << std::endl;
	for (int i=0; i<height; i++) {
		std::cout << i+1 << " ";
		for (int j=0; j<width; j++) {
			Piece* p = board[i][j];
			if (p == NULL)
				std::cout << "  ";
			else
				std::cout << p->toChar() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
