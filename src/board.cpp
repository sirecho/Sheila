/*
 * board.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: Eirik Skogstad
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "piece.h"

Position::Position(int letter, int number) {
	letter_ = letter;
	number_ = number;
}

bool Position::operator==(const Position& other) const {
	return letter() == other.letter() && 
		   number() == other.number();
}

Position Position::stepNorth(int steps) {
	return Position(letter_, number_+steps);
}

Position Position::stepSouth(int steps) {
	return Position(letter_, number_-steps);
}

Position Position::stepEast(int steps) {
	return Position(letter_+steps, number_);
}

Position Position::stepWest(int steps) {
	return Position(letter_-steps, number_);
}

Position Position::stepNorthEast(int steps) {
	return Position(letter_+steps, number_+steps);
}

Position Position::stepNorthWest(int steps) {
	return Position(letter_-steps, number_+steps);
}

Position Position::stepSouthEast(int steps) {
	return Position(letter_+steps, number_-steps);
}

Position Position::stepSouthWest(int steps) {
	return Position(letter_-steps, number_-steps);
}

Board::Board() {

	// Allocate memory for the board
	board_ = new Piece**[height_];
	for (int i=0; i<width_; i++)
		board_[i] = new Piece*[width_];

	// Initialize white pieces
    board_[0][0] = new Rook    (WHITE, Position(0,0));
    board_[0][1] = new Knight  (WHITE, Position(1,0));
    board_[0][2] = new Bishop  (WHITE, Position(2,0));
    board_[0][3] = new Queen   (WHITE, Position(3,0));
    board_[0][4] = new King    (WHITE, Position(4,0));
    board_[0][5] = new Bishop  (WHITE, Position(5,0));
    board_[0][6] = new Knight  (WHITE, Position(6,0));
    board_[0][7] = new Rook    (WHITE, Position(7,0));
    board_[1][0] = new Pawn    (WHITE, Position(0,1));
    board_[1][1] = new Pawn    (WHITE, Position(1,1));
    board_[1][2] = new Pawn    (WHITE, Position(2,1));
    board_[1][3] = new Pawn    (WHITE, Position(3,1));
    board_[1][4] = new Pawn    (WHITE, Position(4,1));
    board_[1][5] = new Pawn    (WHITE, Position(5,1));
    board_[1][6] = new Pawn    (WHITE, Position(6,1));
    board_[1][7] = new Pawn    (WHITE, Position(7,1));

    // Initialize black pieces
    board_[7][0] = new Rook    (BLACK, Position(0,7));
    board_[7][1] = new Knight  (BLACK, Position(1,7));
    board_[7][2] = new Bishop  (BLACK, Position(2,7));
    board_[7][3] = new Queen   (BLACK, Position(3,7));
    board_[7][4] = new King    (BLACK, Position(4,7));
    board_[7][5] = new Bishop  (BLACK, Position(5,7));
    board_[7][6] = new Knight  (BLACK, Position(6,7));
    board_[7][7] = new Rook    (BLACK, Position(7,7));
    board_[6][0] = new Pawn    (BLACK, Position(0,6));
    board_[6][1] = new Pawn    (BLACK, Position(1,6));
    board_[6][2] = new Pawn    (BLACK, Position(2,6));
    board_[6][3] = new Pawn    (BLACK, Position(3,6));
    board_[6][4] = new Pawn    (BLACK, Position(4,6));
    board_[6][5] = new Pawn    (BLACK, Position(5,6));
    board_[6][6] = new Pawn    (BLACK, Position(6,6));
    board_[6][7] = new Pawn    (BLACK, Position(7,6));
}

void Board::clear() {
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			board_[i][j] = NULL;
		}
	}
}

std::vector<Piece*> Board::pieces() {
	std::vector<Piece*> pieces;
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			if (board_[i][j] != NULL)
				pieces.push_back(board_[i][j]);
		}
	}

	return pieces;
}

void Board::placePieces(std::vector<Piece*> pieces) {
	for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		Piece *p = *it;
		board_[p->position().number()][p->position().letter()] = p;
	}
}

void Board::placePiece(Position pos, Piece* piece) {
	board_[pos.number()][pos.letter()] = piece;
}

int Board::evaluate() {
	int whitePiecePoints = 0;
	int blackPiecePoints = 0;
	int whiteSquarePoints = 0;
	int blackSquarePoints = 0;

	for (int i=0; i<height_; i++) {
		for (int j=0; j<width_; j++) {
			Piece *piece = board_[i][j];
			if (piece != NULL) {
				if (piece->getSide() == WHITE) {
					whitePiecePoints += piece->getValue();
					whiteSquarePoints += piece->position().value();
				} else {
					blackPiecePoints += piece->getValue();
					blackSquarePoints += piece->position().value();
				}
			}
		}
	}

	return (whitePiecePoints - blackPiecePoints) + (whiteSquarePoints - blackSquarePoints);
}

bool Board::isOutOfBounds(Position position) {
	bool a = position.number() < height_;
	bool b = position.letter() < width_;
	bool c = position.number() >= 0;
	bool d = position.letter() >= 0;
	return !( a && b && c && d );
}

std::vector<Piece*> Board::pieces(Side side) {

	std::vector<Piece*> pieces;
	for (int i=0; i<height_; i++) {
			for (int j=0; j<width_; j++) {
				Piece *p = board_[i][j];
				if (p != NULL && p->getSide() == side)
					pieces.push_back(board_[i][j]);
			}
	}

	return pieces;
}

std::vector<Piece*> Board::whitePieces() {
	return pieces(WHITE);
}

std::vector<Piece*> Board::blackPieces() {
	return pieces(BLACK);
}

Piece *Board::pieceAt(Position position) {
	if (!isOutOfBounds(position))
		return board_[position.number()][position.letter()];

	return NULL;
}


void Board::capturePiece(Position position) {
	board_[position.number()][position.letter()] = NULL;
}

void Board::movePiece(Position from, Position to) {
    // TODO: Check outofbounds
	Piece *moved = board_[from.number()][from.letter()];
	board_[from.number()][from.letter()] = NULL;
	board_[to.number()][to.letter()] = moved;

	next_to_move_ = next_to_move_ == WHITE ? BLACK : WHITE;
}

char* Board::Describe() {
    char* epd_string = new char[128];
    int string_position = 0;
    char separator = '/';

    // Create representation of piece positions
    for (int rank = BLACK_OFFICER_ROW; rank >= WHITE_OFFICER_ROW; rank--) {
        int blank_squares = 0;
        for (int file=0; file<width_; file++) {
            Piece* piece = board_[rank][file];

            if (piece != NULL && blank_squares > 0) {
                epd_string[string_position++] = blank_squares+'0';
                blank_squares = 0;
                //epd_string[string_position++] = separator;
            } else if (piece == NULL) {
                blank_squares++;
                continue;
            }

            epd_string[string_position++] = piece->toChar();
            //epd_string[string_position++] = separator;
        }

        if (blank_squares > 0) {
            epd_string[string_position++] = blank_squares+'0';
            blank_squares = 0;
        }

        epd_string[string_position++] = separator;
    }

    epd_string[string_position-1] = ' ';

    epd_string[string_position++] = next_to_move_ == WHITE ? 'w' : 'b';
    epd_string[string_position++] = ' ';

    // Create the castling string using a bitmask because it's cool
    char castling[4] = {'K', 'Q', 'k', 'q'};
    unsigned int a = black_can_castle_queen << 3 | black_can_castle_king << 2 | white_can_castle_queen << 1 | white_can_castle_king;

    for (int i = 0; i<4; i++) {
        epd_string[string_position] = char (int (castling[i]) * (a&(unsigned int) pow(2,i))>>i);
        if (int (epd_string[string_position]) != 0)
            string_position++;
    }

    // Terminate and return the string
    epd_string[string_position++] = ' ';
    epd_string[string_position++] = '-';
    epd_string[string_position] = '\0';
    return epd_string;
}

void Board::draw() {

	std::cout << "   ";
	for (int j=0; j<width_*4-1; j++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int i=height_-1; i>=0; i--) {
		std::cout << i+1 << " | ";
		for (int j=0; j<width_; j++) {
			Piece* p = board_[i][j];
			if (p == NULL)
				std::cout << "  | ";
			else
				std::cout << p->toChar() << " " << "|" << " ";
		}
		std::cout << std::endl << "   ";
		for (int j=0; j<width_*4-1; j++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	std::cout << "    A   B   C   D   E   F   G   H" << std::endl;

	std::cout << "\nThe EPD representation if this board is " << Describe() << std::endl;
}
