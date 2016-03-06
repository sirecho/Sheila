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
#include <iterator>
#include "pieces.h"

using namespace std;

int miniMax(Board *board, int depth, bool maxPlayer) {
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
		    	int value = miniMax(board, depth-1, false);
		    	bestValue = bestValue < value ? value : bestValue;

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);
		    }
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
		    	int value = miniMax(board, depth-1, true);
		    	bestValue = bestValue > value ? value : bestValue;

		    	// Revert to previous state
		    	p->setPosition(prevPosition);
		    	board->setSquare(prevPosition, p);
		    	board->setSquare(newPosition, capture);
		    }
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
		    	int value = miniMax(board, 4, false);

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
		    	int value = miniMax(board, 4, true);

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

int main() {
	Board board;

	board.draw();

	bool maxPlayer = true;
	Piece **piece = new Piece*; *piece = NULL;
	Position **move = new Position*; *move = NULL;

	for (int i = 0; i < 10; i++) {
		getNextMove(&board, maxPlayer, piece, move);
		cout << "Moves " << (char)('A'+(*piece)->getCol()) << (*piece)->getRow()+1 << " ";
		(*piece)->move(&board, **move);
		cout << (char) ('A'+(*piece)->getCol()) << (*piece)->getRow()+1 << endl;
		board.draw();
		maxPlayer = !maxPlayer;
	}

	/*
	cout << "Board value: " << board.evaluate() << endl;

	Piece *p = board.getPieceAt(Position(1, 1));
	cout << "Value: " << p->getValue() << endl;
	vector<Position> moves = p->getLegalMoves(&board);

	for (int i = 0; i < moves.size(); i++)
		cout << "Move: " << moves[i].getLetter() << moves[i].getNumber() << endl;

	cout << "Board value: " << board.evaluate() << endl;

	board.movePiece(p->getPosition(), moves[0]);
	board.draw();
	*/
	return 0;
}
