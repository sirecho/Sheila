/*
 * piece.cpp
 *
 *  Created on: Dec 21, 2015
 *      Author: Eirik Skogstad
 */

#include <cstdlib>
#include <vector>
#include "piece.h"

Piece::Piece(Side side, Position position) {
    this->side_ = side;
    this->position_ = position;
    this->character_representation_ = character_representation_;
}

void Piece::move(Board& board, Position to) {
    board.movePiece(position_, to);
    position_ = to;
}

std::vector<Position> Piece::manhattanMoves(Board& board) {
    std::vector<Position> moves;

    // The possible directions {N,E,S,W} a rook R can move in:
    //   N
    // W R E
    //   S

    int start[4] = {
            position_.number()+1, // North
            position_.letter()+1, // East
            position_.number()-1, // South
            position_.letter()-1  // West
    };


    int end[4] = {
            board.width(),      // North
            board.width(),       // East
            0,                    // South
            0                     // West
    };

    // Find possible moves
    for (int k=0; k<4; k++) {
        for (int i=start[k]; k<2 ? i<end[k] : i>=end[k]; i = k<2 ? i+1 : i-1) {
            Position newPos = k%2 ? Position(i, position_.number()) : Position(position_.letter(), i);

            if (board.isOutOfBounds(newPos)) break;

            Piece *piece = board.pieceAt(newPos);

            if (piece == NULL) {
                moves.push_back(newPos);
            }

            // A piece is blocking the path:
            else {
                if (piece->side_ != side_) {
                    moves.push_back(newPos);
                }
                break;
            }
        }
    }

    return moves;
}

std::vector<Position> Piece::diagonalMoves(Board& board) {
    std::vector<Position> moves;

    // The possible directions {X,Y,Z,W} a bishop B can move in:
    // X   Y
    //   B
    // W   Z

    Position posNE = position_.stepNorthEast();
    while (!board.isOutOfBounds(posNE)) {

        Piece *piece = board.pieceAt(posNE);
        if (piece == NULL) {
            moves.push_back(posNE);
        }
        // A piece is blocking the path:
        else {
            if (piece->side_ != side_) {
                moves.push_back(posNE);
            }
            break;
        }
        posNE = posNE.stepNorthEast();
    }

    Position posSE = position_.stepSouthEast();
    while (!board.isOutOfBounds(posSE)) {

        Piece *piece = board.pieceAt(posSE);
        if (piece == NULL) {
            moves.push_back(posSE);
        }
        // A piece is blocking the path:
        else {
            if (piece->side_ != side_) {
                moves.push_back(posSE);
            }
            break;
        }
        posSE = posSE.stepSouthEast();
    }

    Position posNW = position_.stepNorthWest();
    while (!board.isOutOfBounds(posNW)) {

        Piece *piece = board.pieceAt(posNW);
        if (piece == NULL) {
            moves.push_back(posNW);
        }
        // A piece is blocking the path:
        else {
            if (piece->side_ != side_) {
                moves.push_back(posNW);
            }
            break;
        }
        posNW = posNW.stepNorthWest();
    }

    Position posSW = position_.stepSouthWest();
    while (!board.isOutOfBounds(posSW)) {

        Piece *piece = board.pieceAt(posSW);
        if (piece == NULL) {
            moves.push_back(posSW);
        }
        // A piece is blocking the path:
        else {
            if (piece->side_ != side_) {
                moves.push_back(posSW);
            }
            break;
        }
        posSW = posSW.stepSouthWest();
    }

    return moves;
}

std::vector<Position> Pawn::getLegalMoves(Board& board) {

    std::vector<Position> moves;

    // The possible positions {A,B,C,D} a pawn P can move to:
    //   D
    // A B C
    //   P

    Position squareAPosition = this->side_ == WHITE ? position_.stepNorthWest() : position_.stepSouthEast();
    Position squareBPosition = this->side_ == WHITE ? position_.stepNorth() : position_.stepSouth();
    Position squareCPosition = this->side_ == WHITE ? position_.stepNorthEast() : position_.stepSouthWest();

    Position squareXPosition = this->side_ == WHITE ? position_.stepWest() : position_.stepEast();
    Position squareYPosition = this->side_ == WHITE ? position_.stepEast() : position_.stepWest();

    // May advance to B if not blocked by another piece
    Piece *squareBPiece = board.pieceAt(squareBPosition);
    if (!board.isOutOfBounds(squareBPosition) && squareBPiece == NULL) {
        moves.push_back(squareBPosition);
    }

    // May advance to D if this is the first move
    if (this->side_ == WHITE && board.isPawnRow(side_, position_) && board.pieceAt(position_.stepNorth(2)) == NULL && squareBPiece == NULL) {
        moves.push_back(position_.stepNorth().stepNorth());
    } else if (this->side_ == BLACK && board.isPawnRow(side_, position_) && board.pieceAt(position_.stepSouth(2)) == NULL && squareBPiece == NULL) {
        moves.push_back(position_.stepSouth().stepSouth());
    }

    // May attack A and C if these squares have opposition pieces
    Piece *squareAPiece = board.pieceAt(squareAPosition);
    if (squareAPiece != NULL && squareAPiece->getSide() != this->side_) {
        moves.push_back(squareAPosition);
    }
    Piece *squareCPiece = board.pieceAt(squareCPosition);
    if (squareCPiece != NULL && squareCPiece->getSide() != this->side_) {
        moves.push_back(squareCPosition);
    }

    // En passant rule
    // if ((side_ == WHITE && position_.number() == WHITE_ENPASSANT_ROW) ||
    //         (side_ == BLACK && position_.number() == BLACK_ENPASSANT_ROW)) {

    //     Position *enPassantPosition = board.getEnPassantPosition();

    //     if (enPassantPosition ==  squareAPosition) {
    //         moves.push_back(squareAPosition);
    //     }

    //     if (enPassantPosition ==  squareCPosition) {
    //         moves.push_back(squareCPosition);
    //     }
    // }

    return moves;
}

void Pawn::move(Board& board, Position to) {
    // Set en passant
    // if (abs(to.number - position_.number) == 2) {
    //     int enPassantRow = (position_.number - to.number) / 2;
    //     Position enPassantPosition = Position(position_.letter, enPassantRow);
    //     board.setEnPassant(enPassantPosition);
    // }

    board.movePiece(position_, to);
    position_ = to;
}

std::vector<Position> Rook::getLegalMoves(Board& board) {
    return manhattanMoves(board);
}

std::vector<Position> Knight::getLegalMoves(Board& board) {
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
        Position p1(position_.letter()+letters[k], position_.number()+numbers[k]);
        Piece *a = board.pieceAt(p1);
        Position p2(position_.letter()+letters[k], position_.number()-numbers[k]);
        Piece *b = board.pieceAt(p2);

        if (!board.isOutOfBounds(p1) && (a == NULL || a->getSide() != side_)) {
            moves.push_back(p1);
        }

        if (!board.isOutOfBounds(p2) && (b == NULL || b->getSide() != side_)) {
            moves.push_back(p2);
        }
    }

    return moves;
}

std::vector<Position> Bishop::getLegalMoves(Board& board) {
    return this->diagonalMoves(board);
}

std::vector<Position> Queen::getLegalMoves(Board& board) {
    std::vector<Position> moves;

    // Concatenate diagonal and Manhattan moves:
    std::vector<Position> diagonal = diagonalMoves(board);
    std::vector<Position> manhattan = manhattanMoves(board);

    moves.reserve( diagonal.size() + manhattan.size() ); // preallocate memory
    moves.insert( moves.end(), diagonal.begin(), diagonal.end() );
    moves.insert( moves.end(), manhattan.begin(), manhattan.end() );

    return moves;
}

std::vector<Position> King::getLegalMoves(Board& board) {
    std::vector<Position> moves;

    // The King can move one step in any direction:
    Position allDirections[8] = {
            position_.stepNorth(),
            position_.stepNorthEast(),
            position_.stepEast(),
            position_.stepSouthEast(),
            position_.stepSouth(),
            position_.stepSouthWest(),
            position_.stepWest(),
            position_.stepNorthWest()
    };

    for (int i=0; i<8; i++) {
        if (board.isOutOfBounds(allDirections[i])) continue;

        Piece *piece = board.pieceAt(allDirections[i]);

        if (piece == NULL || piece->getSide() != side_) {
            moves.push_back(allDirections[i]);
        }
    }

    return moves;
}
