/*
 * board.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Eirik Skogstad
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "side.h"

class Position;
class Piece;

class Board {

  public:

    virtual ~Board() {}

    // Functions for placing and removing pieces on the board
    virtual void placePieces(std::vector<Piece*> pieces) = 0;
    virtual void placePiece(Position pos, Piece* piece) = 0;
    virtual void clear() = 0;

    // Functions for extracting pointers to pieces on the board
    virtual Piece *pieceAt(Position position) = 0;
    virtual std::vector<Piece*> pieces() = 0;
    virtual std::vector<Piece*> pieces(Side side) = 0;

    // Evaluate the current advantage for the white player.
    // In chess terms, this is the evaluation of the position boiled down to a
    // single numeric value.
    // A higher value signifies more advantage for white and vice versa.
    virtual int evaluate() = 0;

    virtual Piece* movePiece(Position from, Position to) = 0;

    virtual int width() = 0;
    virtual bool isOutOfBounds(Position position) = 0;

    
    virtual Position* getEnPassantPosition() = 0;
    virtual bool isWhitePawnRow(Position position) = 0;
    virtual bool isBlackPawnRow(Position position) = 0;

    // Return a string representation of the current position
    virtual char* Describe() = 0;

    // TODO: This has no business here, should be moved to a Graphics/Console class.
    virtual void draw() = 0;
};

#endif /* BOARD_H_ */
