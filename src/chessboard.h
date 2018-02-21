/*
 * chessboard.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Eirik Skogstad
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include "board.h"

class Position;

class ChessBoard : public Board {
  public:
  	virtual ~ChessBoard() {}

};

#endif /* CHESSBOARD_H_ */