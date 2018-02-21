/*
 * standardboard.h
 *
 *  Created on: Dec 21, 2015
 *      Author: Eirik Skogstad
 */

#ifndef STANDARDBOARD_H_
#define STANDARDBOARD_H_

#include "board.h"
#include "side.h"

class Piece;
class Position;

const int WHITE_OFFICER_ROW     =   0;
const int WHITE_PAWN_ROW        =   1;
const int WHITE_ENPASSANT_ROW   =   5;
const int BLACK_OFFICER_ROW     =   7;
const int BLACK_PAWN_ROW        =   6;
const int BLACK_ENPASSANT_ROW   =   4;

class StandardBoard : public Board {
  public:
    StandardBoard();
    ~StandardBoard();

    // Functions for placing and removing pieces on the board
    void placeAllPieces(Piece ***newBoard);
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

    Position* getEnPassantPosition();

    // Return a string representation of the current position
    char* Describe();

    // TODO: This has no business here, should be moved to a Graphics/Console class.
    void draw();

    int width();

    bool isOutOfBounds(Position position);
    bool isWhitePawnRow(Position position);
    bool isBlackPawnRow(Position position);

  private:
    static const int height_ = 8;
    static const int width_  = 8;
    Piece ***board_;

    bool white_can_castle_king = true;
    bool white_can_castle_queen = true;
    bool black_can_castle_king = true;
    bool black_can_castle_queen = true;

    Side next_to_move_ = WHITE;
};

#endif /* STANDARDBOARD_H_ */
