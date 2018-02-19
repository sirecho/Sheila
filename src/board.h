/*
 * board.h
 *
 *  Created on: Dec 21, 2015
 *      Author: Eirik Skogstad
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "side.h"

class Piece;

const int WHITE_OFFICER_ROW     =   0;
const int WHITE_PAWN_ROW        =   1;
const int WHITE_ENPASSANT_ROW   =   5;
const int BLACK_OFFICER_ROW     =   7;
const int BLACK_PAWN_ROW        =   6;
const int BLACK_ENPASSANT_ROW   =   4;

class Position {
  public:
    Position() : letter_(0), number_(0) {}
    Position(int letter, int number);

    bool operator==(const Position& other) const;

    int letter() const { return letter_; }
    int number() const { return number_; }
    int value()  const { if (number_ <= 4 && number_ >= 3) return 10; return 0; }

    // Functions for taking n=steps steps in a given direction.
    // myPosition.stepNorth() will return the position at one step north of
    // myPosition.
    Position stepNorth     (int steps = 1);
    Position stepNorthEast (int steps = 1);
    Position stepNorthWest (int steps = 1);
    Position stepSouth     (int steps = 1);
    Position stepSouthEast (int steps = 1);
    Position stepSouthWest (int steps = 1);
    Position stepEast      (int steps = 1);
    Position stepWest      (int steps = 1);

  private:
    int letter_;
    int number_;
};

class Board {
    friend class Piece;
    friend class King;
    friend class Queen;
    friend class Bishop;
    friend class Knight;
    friend class Rook;
    friend class Pawn;

  public:
    Board();

    // Functions for placing and removing pieces on the board
    void placeAllPieces(Piece ***newBoard) { board_ = newBoard; }
    void placePieces(std::vector<Piece*> pieces);
    void placePiece(Position pos, Piece* piece);
    void clear();

    // Functions for extracting pointers to pieces on the board
    Piece *pieceAt(Position position);
    std::vector<Piece*> pieces();
    std::vector<Piece*> pieces(Side side);
    std::vector<Piece*> whitePieces();
    std::vector<Piece*> blackPieces();

    // Evaluate the current advantage for the white player.
    // In chess terms, this is the evaluation of the position boiled down to a
    // single numeric value.
    // A higher value signifies more advantage for white and vice versa.
    int evaluate();

    void capturePiece(Position position);
    void movePiece(Position from, Position to);

    Position *getEnPassantPosition() { return 0; }

    // Return a string representation of the current position
    char* Describe();

    // TODO: This has no business here, should be moved to a Graphics/Console class.
    void draw();

  private:
    static const int height_ = 8;
    static const int width_  = 8;
    Piece ***board_;

    bool white_can_castle_king = true;
    bool white_can_castle_queen = true;
    bool black_can_castle_king = true;
    bool black_can_castle_queen = true;

    Side next_to_move_ = WHITE;

    int height() { return height_; }
    int width()  { return width_; }
    bool isOutOfBounds(Position position);
};

#endif /* BOARD_H_ */
