/*
 * IMoveDecision.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Eirik Skogstad
 */

#ifndef IMOVEDECISION_H_
#define IMOVEDECISION_H_

#include "piece.h"

class IMoveDecision {
	public:
	virtual void getNextMove(Board *board, bool maxPlayer, Piece **pieceToMove, Position **moveTo) = 0;
};

#endif /* IMOVEDECISION_H_ */