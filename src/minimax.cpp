// by echo, Jan 28 18

#include <vector>
#include <climits>
#include "board.h"
#include "piece.h"
#include "minimax.h"

int MiniMax::miniMaxShort(Board& board, int depth, int alpha, int beta, bool maxPlayer) {
		if (depth == 0) return board.evaluate();

		std::vector<Piece*> pieces = maxPlayer ? board.whitePieces() : board.blackPieces();

		int bestValue = maxPlayer ? INT_MIN : INT_MAX;

		for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			Piece *p = *it;
			// Save current state
			Position prevPosition = p->position();

			std::vector<Position> moves = p->getLegalMoves(board);

			for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {
				Position newPosition = *jt;
				Piece* capture = board.pieceAt(newPosition);

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
				p->placeAt(prevPosition);
				board.placePiece(prevPosition, p);
				board.placePiece(newPosition, capture);

				if (beta <= alpha) break;
			}
			if (beta <= alpha) break;
		}

		return bestValue;
	}

	void MiniMax::getNextMove(Board& board, bool maxPlayer, Piece **piece, Position **move) {
		std::vector<Piece*> allPieces = board.pieces();
		std::vector<Piece*> pieces = maxPlayer ? board.whitePieces() : board.blackPieces();

		if (maxPlayer) {
			int bestValue = INT_MIN;

			for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			    Piece *p = *it;
			    // Save current state
				Position prevPosition = p->position();

				std::vector<Position> moves = p->getLegalMoves(board);

			    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {

			    	Position newPosition = *jt;
					Piece* capture = board.pieceAt(newPosition);

			    	p->move(board, *jt);
			    	int value = miniMaxShort(board, 3, INT_MIN, INT_MAX, false);

			    	if (value > bestValue) {
			    		bestValue = value;
			    		*piece = p;
			    		delete *move;
			    		*move = new Position((*jt).letter(), (*jt).number());
			    	}

			    	// Revert to previous state
			    	p->placeAt(prevPosition);
			    	board.placePiece(prevPosition, p);
			    	board.placePiece(newPosition, capture);
			    }
			}

			board.placePieces(allPieces);
		} else {
			int bestValue = INT_MAX;

			for(std::vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			    Piece *p = *it;
			    // Save current state
				Position prevPosition = p->position();

				std::vector<Position> moves = p->getLegalMoves(board);

			    for(std::vector<Position>::iterator jt = moves.begin(); jt != moves.end(); ++jt) {

			    	Position newPosition = *jt;
					Piece* capture = board.pieceAt(newPosition);

					p->move(board, *jt);
			    	int value = miniMaxShort(board, 3, INT_MIN, INT_MAX, true);

			    	if (value < bestValue) {
			    		bestValue = value;
			    		*piece = p;
			    		delete *move;
			    		*move = new Position((*jt).letter(), (*jt).number());
			    	}

			    	// Revert to previous state
			    	p->placeAt(prevPosition);
			    	board.placePiece(prevPosition, p);
			    	board.placePiece(newPosition, capture);
			    }
			}

			board.placePieces(allPieces);
		}
	}