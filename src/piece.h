/*
 * piece.h
 *
 *  Created on: Dec 21, 2015
 *      Author: Eirik Skogstad
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <vector>
#include "board.h"
#include "side.h"
#include "position.h"

class Piece {
  public:
    Piece(Side side, Position position);
    virtual ~Piece(){}

    Side getSide() { return side_; }
    short getValue() { return value_; }

    Position position() { return position_; }
    void placeAt(Position position) { this->position_ = position; }

    // Functions returning positions for legal moves
    std::vector<Position> manhattanMoves(Board *board);
    std::vector<Position> diagonalMoves(Board *board);

    virtual std::vector<Position> getLegalMoves(Board *board) = 0;
    virtual void move(Board *board, Position to);

    char toChar() { return character_representation_; }

    bool operator<(const Piece &rhs) const { return value_ < rhs.value_; }

  protected:
    Side side_;
    short value_;
    Position position_;
    char character_representation_;
};

class Pawn: public Piece {
private:
    bool enPassant;
public:
    Pawn(Side side, Position position) : Piece(side, position) { enPassant = false; character_representation_ = side == WHITE ? 'P' : 'p'; value_ = 10; }
    std::vector<Position> getLegalMoves(Board *board);
    void move(Board *board, Position to);
    bool canEnPassant() { return enPassant; }
};

class Rook: public Piece {
public:
    Rook(Side side, Position position) : Piece(side, position) { character_representation_ = side == WHITE ? 'R' : 'r'; value_ = 50; }
    std::vector<Position> getLegalMoves(Board *board);
};

class Knight: public Piece {
public:
    Knight(Side side, Position position) : Piece(side, position) { character_representation_ = side == WHITE ? 'N' : 'n'; value_ = 30; }
    std::vector<Position> getLegalMoves(Board *board);
};

class Bishop: public Piece {
public:
    Bishop(Side side, Position position) : Piece(side, position) { character_representation_ = side == WHITE ? 'B' : 'b'; value_ = 30; }
    std::vector<Position> getLegalMoves(Board *board);
};

class Queen: public Piece {
public:
    Queen(Side side, Position position) : Piece(side, position) { character_representation_ = side == WHITE ? 'Q' : 'q'; value_ = 90; }
    std::vector<Position> getLegalMoves(Board *board);
};

class King: public Piece {
public:
    King(Side side, Position position) : Piece(side, position) { character_representation_ = side == WHITE ? 'K' : 'k'; value_ = 1000;	}
    std::vector<Position> getLegalMoves(Board *board);
};

#endif /* PIECE_H_ */
