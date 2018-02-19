//============================================================================
// Name        : sheila.cpp
// Author      : Eirik Skogstad
// Version     :
// Copyright   : 
// Description : A chess playing agent.
//============================================================================

#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iterator>
#include <algorithm>
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

	board.pieceAt(Position(3,1))->move(&board, Position(3,3));
	board.draw();

	for (int i = 0; i < moves; i++) {
	    std::clock_t start = clock();
		moveDecision.getNextMove(&board, maxPlayer, piece, move);
		double duration = (clock() - start) / (double) CLOCKS_PER_SEC;

		cout << "Moves " << (char)('A'+(*piece)->position().letter()) << (*piece)->position().number()+1
		     << "\nTime: " << duration << endl;

		(*piece)->move(&board, **move);
		cout << (char) ('A'+(*piece)->position().letter()) << (*piece)->position().number()+1 << endl;
		board.draw();
		maxPlayer = !maxPlayer;
	}
}

void playerMove(Board *board) {

    // TODO: Deprecated. Player cannot talk directly to the board.

//	Position startMove, endMove;
//
//	do {
//		std::string move;
//		cout << "Enter move: ";
//		getline(cin, move);
//
//		if (move.length() != 5) continue;
//
//		int firstCol = (int) move[0]-'a';
//		int firstNum = (int) move[1]-'0'-1;
//		int secondCol = (int) move[3]-'a';
//		int secondNum = (int) move[4]-'0'-1;
//
//		startMove = Position(firstCol, firstNum);
//		endMove = Position(secondCol, secondNum);
//
//	} while(board->isOutOfBounds(startMove) || board->isOutOfBounds(endMove));
//
//	board->pieceAt(startMove)->move(board, endMove);

}

//}

int main() {

	StandardBoard board;
	board.draw();

	bool maxPlayer = false;
	Piece **piece = new Piece*; *piece = NULL;
	Position **move = new Position*; *move = NULL;

	while(1) {
	    autoPlay(100);
//		playerMove(&board);
//		board.draw();
//		getNextMove(&board, maxPlayer, piece, move);
//		(*piece)->move(&board, **move);
//		board.draw();
	}


	return 0;
}
