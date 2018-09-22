#ifndef MOCKBOARD_H_
#define MOCKBOARD_H_

#include "gmock/gmock.h"
#include "board.h"

class MockBoard : public Board {
 public:
	MOCK_METHOD0(clear, void());
	MOCK_METHOD0(width, int());
	MOCK_METHOD0(evaluate, int());
	MOCK_METHOD0(Describe, char*());
	MOCK_METHOD0(draw, void());
	MOCK_METHOD0(getEnPassantPosition, Position*());
	MOCK_METHOD0(pieces, std::vector<Piece*>());
	MOCK_METHOD1(placePieces, void(std::vector<Piece*> pieces));
	MOCK_METHOD1(pieceAt, Piece*(Position position));
	MOCK_METHOD1(capturePiece, void(Position position));
	MOCK_METHOD1(isOutOfBounds, bool(Position position));
	MOCK_METHOD1(isWhitePawnRow, bool(Position position));
	MOCK_METHOD1(isBlackPawnRow, bool(Position position));
	MOCK_METHOD1(pieces, std::vector<Piece*>(Side side));
	MOCK_METHOD2(placePiece, void(Position pos, Piece* piece));
	MOCK_METHOD2(movePiece, void(Position from, Position to));	
};

#endif /* MOCKBOARD_H_ */