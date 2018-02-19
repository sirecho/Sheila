// by echo, Jan 28 18

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include <vector>
#include <climits>
#include "piece.h"
#include "movedecision.h"

class MiniMax : public IMoveDecision {
	public:
	MiniMax() {};
	int miniMaxShort(Board *board, int depth, int alpha, int beta, bool maxPlayer);
	void getNextMove(Board *board, bool maxPlayer, Piece **piece, Position **move);
};

#endif /* MINIMAX_H_ */