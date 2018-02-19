//============================================================================
// Name        : sheila.cpp
// Author      : Eirik Skogstad
// Version     :
// Copyright   : 
// Description : A chess playing agent.
//============================================================================

#include <iostream>
#include <ctime>
#include "standardboard.h"
#include "piece.h"
#include "minimax.h"

using namespace std;

void autoPlay(int moves) {
	StandardBoard board;
	MiniMax moveDecision;

	board.draw();

	bool maxPlayer = false;
	Piece **piece = new Piece*; *piece = NULL;
	Position **move = new Position*; *move = NULL;

	board.pieceAt(Position(3,1))->move(board, Position(3,3));
	board.draw();

	for (int i = 0; i < moves; i++) {
	    std::clock_t start = clock();
		moveDecision.getNextMove(board, maxPlayer, piece, move);
		double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

		cout << "Moves " << (char)('A'+(*piece)->position().letter()) << (*piece)->position().number()+1
		     << "\nTime: " << duration << endl;

		(*piece)->move(board, **move);
		cout << (char) ('A'+(*piece)->position().letter()) << (*piece)->position().number()+1 << endl;
		board.draw();
		maxPlayer = !maxPlayer;
	}

	// *piece is deleted in StandardBoard dtor
	delete piece;
	delete *move;
	delete move;
}

int main() {
	autoPlay(100);
	return 0;
}
