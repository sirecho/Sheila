/*
 * movedecision.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Eirik Skogstad
 */

#ifndef MOVEDECISION_H_
#define MOVEDECISION_H_

#include "piece.h"

class MoveDecision {
	public:
	virtual void getNextMove(Board *board, bool maxPlayer, Piece **pieceToMove, Position **moveTo) = 0;
};

#endif /* MOVEDECISION_H_ */