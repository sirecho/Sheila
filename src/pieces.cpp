/*
 * pieces.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: echo
 */

#include <cstdlib>
#include <vector>
#include "pieces.h"

Piece::Piece(Side side, int value) {
	this->side = side;
	this->value = value;
}

void Piece::move(Position to) {
	position = to;
}

std::vector<Position> Piece::getLegalManhattanMoves(Board *board) {
	std::vector<Position> moves;

	// The possible directions {N,E,S,W} a rook R can move in:
	//   N
	// W R E
	//   S

	int start[4] = {position.getNumber()+1, // North
					position.getLetter()+1, // East
					position.getNumber()-1,	// South
					position.getLetter()-1	// West
	};

	int end[4] = {board->getHeight(), 	// North
				  board->getWidth(), 	// East
				  0,					// South
				  0						// West
	};

	// Find possible moves
	for (int k=0; k<4; k++) {
		for (int i=start[k]; i<end[k]; i++) {
			Position newPos(position.getLetter(), i);
			Piece *piece = board->getPieceAt(newPos);


			if (piece == NULL) {
				moves.push_back(newPos);
			}
			// A piece is blocking the path:
			else {
				if (piece->side != side) {
					moves.push_back(newPos);
				}
				break;
			}
		}
	}

	return moves;
}

std::vector<Position> Piece::getLegalDiagonalMoves(Board *board) {
	std::vector<Position> moves;

	// The possible directions {X,Y,Z,W} a bishop B can move in:
	// X   Y
	//   B
	// W   Z

	Position posNE = position.stepNorthEast();
	for (int i=2; !board->isOutOfBounds(posNE); i++) {

		Piece *piece = board->getPieceAt(posNE);
		if (piece == NULL) {
			moves.push_back(posNE);
		}
		// A piece is blocking the path:
		else {
			if (piece->side != side) {
				moves.push_back(posNE);
			}
			break;
		}
		posNE = posNE.stepNorthEast(i);
	}

	Position posSE = position.stepSouthEast();
	for (int i=2; !board->isOutOfBounds(posSE); i++) {

		Piece *piece = board->getPieceAt(posSE);
		if (piece == NULL) {
			moves.push_back(posSE);
		}
		// A piece is blocking the path:
		else {
			if (piece->side != side) {
				moves.push_back(posSE);
			}
			break;
		}
		posSE = posSE.stepSouthEast(i);
	}

	Position posNW = position.stepNorthWest();
	for (int i=2; !board->isOutOfBounds(posNW); i++) {

		Piece *piece = board->getPieceAt(posNW);
		if (piece == NULL) {
			moves.push_back(posNW);
		}
		// A piece is blocking the path:
		else {
			if (piece->side != side) {
				moves.push_back(posNW);
			}
			break;
		}
		posNW = posNW.stepNorthWest(i);
	}

	Position posSW = position.stepSouthWest();
	for (int i=2; !board->isOutOfBounds(posSW); i++) {

		Piece *piece = board->getPieceAt(posSW);
		if (piece == NULL) {
			moves.push_back(posSW);
		}
		// A piece is blocking the path:
		else {
			if (piece->side != side) {
				moves.push_back(posSW);
			}
			break;
		}
		posSW = posSW.stepSouthWest(i);
	}

	return moves;
}


Pawn::Pawn(Side side, int value) : Piece(side, value) {
	enPassant = false;
}

std::vector<Position> Pawn::getLegalMoves(Board *board) {

	std::vector<Position> moves;

	// The possible positions {A,B,C,D} a pawn P can move to:
	//   D
	// A B C
	// X P Y

	Position squareAPosition = this->side == WHITE ? position.stepNorthWest() : position.stepSouthEast();
	Position squareBPosition = this->side == WHITE ? position.stepNorth() : position.stepSouth();
	Position squareCPosition = this->side == WHITE ? position.stepNorthEast() : position.stepSouthWest();
	Position squareXPosition = this->side == WHITE ? position.stepWest() : position.stepEast();
	Position squareYPosition = this->side == WHITE ? position.stepEast() : position.stepWest();

	// May advance to B if not blocked by another piece
	Piece *squareBPiece = board->getPieceAt(squareBPosition);
	if (squareBPiece == NULL) {
		moves.push_back(squareBPosition);
	}

	// May advance to D if this is the first move
	if (this->side == WHITE && position.getNumber() == WHITE_PAWN_ROW) {
		moves.push_back(position.stepNorth().stepNorth());
	} else if (this->side == BLACK && position.getNumber() == BLACK_PAWN_ROW) {
		moves.push_back(position.stepSouth().stepSouth());
	}

	// May attack A and C if these squares have opposition pieces
	Piece *squareAPiece = board->getPieceAt(squareAPosition);
	if (squareAPiece != NULL && squareAPiece->getSide() != this->side) {
		moves.push_back(squareAPosition);
	}
	Piece *squareCPiece = board->getPieceAt(squareCPosition);
	if (squareCPiece != NULL && squareCPiece->getSide() != this->side) {
		moves.push_back(squareCPosition);
	}

	// En passant rule
	if ((side == WHITE && position.getNumber() == WHITE_ENPASSANT_ROW) ||
		(side == BLACK && position.getNumber() == BLACK_ENPASSANT_ROW)) {
		Pawn *squareXPiece = dynamic_cast<Pawn *>(board->getPieceAt(squareXPosition));
		Pawn *squareYPiece = dynamic_cast<Pawn *>(board->getPieceAt(squareYPosition));

		if (squareAPiece == NULL && squareXPiece != NULL && squareXPiece->side != side && squareXPiece->canEnPassant()) {
			moves.push_back(squareAPosition);
		}

		if (squareCPiece == NULL && squareYPiece != NULL && squareYPiece->side != side && squareYPiece->canEnPassant()) {
			moves.push_back(squareCPosition);
		}
	}

	return moves;
}

void Pawn::move(Board *board, Position to) {
	Piece::move(to);
	Position capture = to;

	// Handle capture
	if (to.getLetter() != position.getLetter()) {

		// En passant
		if (board->getPieceAt(to) == NULL) {
			capture = side == WHITE ? to.stepSouth() : to.stepNorth();
		}

		board->capturePiece(capture);
	}

	board->movePiece(position, to);
	position = to;
}

std::vector<Position> Rook::getLegalMoves(Board *board) {
	return getLegalManhattanMoves(board);
}

std::vector<Position> Knight::getLegalMoves(Board *board) {
	std::vector<Position> moves;

	// The possible locations {A,B,C,D,E,F,G,H} a knight K can move to:
	// # B # C #
	// A # # # D
	// # # K # #
	// H # # # E
	// # G # F #

	int letters[4] = {-2, 	// A, H
					  -1, 	// B, G
					   1,	// C, F
					   2	// D, E
	};

	int numbers[4] = { 1, // A, !H
					   2, // B, !G
					   2, // C, !F
					   1  // D, !E
	};

	for (int k=0; k<4; k++) {
		Position p1(position.getLetter()+letters[k], position.getNumber()+numbers[k]);
		Piece *a = board->getPieceAt(p1);
		Position p2(position.getLetter()+letters[k], position.getNumber()-numbers[k]);
		Piece *b = board->getPieceAt(p2);

		if (!board->isOutOfBounds(p1) && (a == NULL || a->getSide() != side)) {
			moves.push_back(p1);
		}

		if (!board->isOutOfBounds(p1) && (b == NULL || b->getSide() != side)) {
			moves.push_back(p2);
		}
	}

	return moves;
}

std::vector<Position> Bishop::getLegalMoves(Board *board) {
	return this->getLegalDiagonalMoves(board);
}

std::vector<Position> Queen::getLegalMoves(Board *board) {
	std::vector<Position> moves;

	// Concatenate diagonal and Manhattan moves:
	std::vector<Position> diagonal = getLegalDiagonalMoves(board);
	std::vector<Position> manhattan = getLegalManhattanMoves(board);

	moves.reserve( diagonal.size() + manhattan.size() ); // preallocate memory
	moves.insert( moves.end(), diagonal.begin(), diagonal.end() );
	moves.insert( moves.end(), manhattan.begin(), manhattan.end() );

	return moves;
}

std::vector<Position> King::getLegalMoves(Board *board) {
	std::vector<Position> moves;

	// The King can move one step in any direction:
	Position allDirections[8] = {
		position.stepNorth(),
		position.stepNorthEast(),
		position.stepEast(),
		position.stepSouthEast(),
		position.stepSouth(),
		position.stepSouthWest(),
		position.stepWest(),
		position.stepNorthWest()
	};

	for (int i=0; i<8; i++) {
		Piece *piece = board->getPieceAt(allDirections[i]);

		if (piece == NULL || piece->getSide() != side) {
			moves.push_back(allDirections[i]);
		}
	}

	return moves;
}
