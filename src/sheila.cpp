//============================================================================
// Name        : sheila.cpp
// Author      : Eirik Skogstad
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "pieces.h"

using namespace std;

int miniMaxShort(Board *board, int depth, int alpha, int beta, bool maxPlayer) {
	if (depth == 0) return board->evaluate();

	vector<Piece*> allPieces = board->get();
	vector<Piece*> pieces = maxPlayer ? board->getWhitePieces() : board->getBlackPieces();

	int bestValue = maxPlayer ? INT_MIN : INT_MAX;

	for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		Piece *p = *it;
		// Save current state
		Position prevPosition = p->getPosition();

		vector<Position> moves = p->getLegalMoves(board);

		for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {
			Position newPosition = *jt;
			Piece* capture = board->getPieceAt(newPosition);

			p->move(board, *jt);
			int value = miniMaxShort(board, depth-1, alpha, beta, !maxPlayer);

			if (maxPlayer) {
				bestValue = bestValue < value ? value : bestValue;
				alpha = alpha < value ? value : alpha;
			} else {
				bestValue = bestValue > value ? value : bestValue;
				beta = beta > value ? value : beta;
			}

			// Revert to previous state
			p->setPosition(prevPosition);
			board->setSquare(prevPosition, p);
			board->setSquare(newPosition, capture);

			if (beta <= alpha) break;
		}
		if (beta <= alpha) break;
	}

	return bestValue;
}

int miniMax(Board *board, int depth, int alpha, int beta, bool maxPlayer) {
	if (depth == 0) return board->evaluate();

	vector<Piece*> allPieces = board->get();
	vector<Piece*> pieces = maxPlayer ? board->getWhitePieces() : board->getBlackPieces();

	if (maxPlayer) {
		int bestValue = INT_MIN;

		for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		    Piece *p = *it;
		    // Save current state
			Position prevPosition = p->getPosition();

		    vector<Position> moves = p->getLegalMoves(board);

		    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {
				Position newPosition = *jt;
				Piece* capture = board->getPieceAt(newPosition);

		    	p->move(board, *jt);
		    	int value = miniMax(board, depth-1, alpha, beta, false);
		    	bestValue = bestValue < value ? value : bestValue;
		    	alpha = alpha < value ? value : alpha;

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);

		    	if (beta <= alpha) break;
		    }
		    if (beta <= alpha) break;
		}

		return bestValue;
	} else {
		int bestValue = INT_MAX;

		for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		    Piece *p = *it;
		    // Save current state
			Position prevPosition = p->getPosition();

		    vector<Position> moves = p->getLegalMoves(board);

		    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {

				Position newPosition = *jt;
				Piece* capture = board->getPieceAt(newPosition);

		    	p->move(board, *jt);
		    	int value = miniMax(board, depth-1, alpha, beta, true);
		    	bestValue = bestValue > value ? value : bestValue;
		    	beta = beta > value ? value : beta;

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);

		    	if (beta <= alpha) break;
		    }

		    if (beta <= alpha) break;
		}

		return bestValue;
	}
}

void getNextMove(Board *board, bool maxPlayer, Piece **piece, Position **move) {
	vector<Piece*> allPieces = board->get();
	vector<Piece*> pieces = maxPlayer ? board->getWhitePieces() : board->getBlackPieces();

	if (maxPlayer) {
		int bestValue = INT_MIN;

		for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		    Piece *p = *it;
		    // Save current state
			Position prevPosition = p->getPosition();

			vector<Position> moves = p->getLegalMoves(board);

		    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {

		    	Position newPosition = *jt;
				Piece* capture = board->getPieceAt(newPosition);

		    	p->move(board, *jt);
		    	int value = miniMaxShort(board, 5, INT_MIN, INT_MAX, false);

		    	if (value > bestValue) {
		    		bestValue = value;
		    		*piece = p;
		    		*move = new Position((*jt).getNumber(), (*jt).getLetter());
		    	}

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);
		    }
		}

		board->set(allPieces);
	} else {
		int bestValue = INT_MAX;

		for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		    Piece *p = *it;
		    // Save current state
			Position prevPosition = p->getPosition();

			vector<Position> moves = p->getLegalMoves(board);

		    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {

		    	Position newPosition = *jt;
				Piece* capture = board->getPieceAt(newPosition);

				p->move(board, *jt);
		    	int value = miniMaxShort(board, 5, INT_MIN, INT_MAX, true);

		    	if (value < bestValue) {
		    		bestValue = value;
		    		*piece = p;
		    		*move = new Position((*jt).getNumber(), (*jt).getLetter());
		    	}

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);
		    }
		}

		board->set(allPieces);
	}
}

void autoPlay(int moves) {
	Board board;

	board.draw();

	bool maxPlayer = false;
	Piece **piece = new Piece*; *piece = NULL;
	Position **move = new Position*; *move = NULL;

	board.getPieceAt(Position(1,3))->move(&board, Position(3,3));
	board.draw();

	std::clock_t start = clock();
	for (int i = 0; i < moves; i++) {
		getNextMove(&board, maxPlayer, piece, move);


		cout << "Moves " << (char)('A'+(*piece)->getCol()) << (*piece)->getRow()+1 << endl;

		(*piece)->move(&board, **move);
		cout << (char) ('A'+(*piece)->getCol()) << (*piece)->getRow()+1 << endl;
		board.draw();
		maxPlayer = !maxPlayer;
	}

	double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	cout << "Time: " << duration << endl;
}

void playerMove(Board *board) {

	Position startMove, endMove;

	do {
		std::string move;
		cout << "Enter move: ";
		getline(cin, move);

		if (move.length() != 5) continue;

		int firstCol = (int) move[0]-'a';
		int firstNum = (int) move[1]-'0'-1;
		int secondCol = (int) move[3]-'a';
		int secondNum = (int) move[4]-'0'-1;

		startMove = Position(firstNum, firstCol);
		endMove = Position(secondNum, secondCol);

	} while(board->isOutOfBounds(startMove) || board->isOutOfBounds(endMove));

	board->getPieceAt(startMove)->move(board, endMove);

}

int main() {
	Board board;
	board.draw();

	bool maxPlayer = false;
	Piece **piece = new Piece*; *piece = NULL;
	Position **move = new Position*; *move = NULL;

	while(1) {
		playerMove(&board);
		board.draw();
		getNextMove(&board, maxPlayer, piece, move);
		(*piece)->move(&board, **move);
		board.draw();
	}


	return 0;
}
