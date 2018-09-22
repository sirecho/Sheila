#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "piece.h"
#include "mockboard.h"

using ::testing::_;
using ::testing::Return;

/* Summary of tests:
 *
 * Bounds: A pawn cannot move out of bounds.
 * MoveOne: A pawn can move one square ahead.
 * MoveTwo: A pawn can move two squares ahead from the second rank.
 * Blocked: A pawn cannot move if it is blocked.
 * Capture: A pawn can capture to the left and right.
 * EnPassant: A pawn can capture en passant.
 */

namespace {

Pawn placePawn(Side side, Position position, Board& board) {
	Pawn pawn(side, position);
	board.placePiece(position, &pawn);
	return pawn;
}

TEST(PawnTest, Bounds) {
	MockBoard mockBoard;
	EXPECT_CALL(mockBoard, isOutOfBounds(_))
		.WillRepeatedly(Return(true));

	Pawn pawn = placePawn(WHITE, Position(0,0), mockBoard);
	std::vector<Position> legalMoves = pawn.getLegalMoves(mockBoard);
	EXPECT_EQ(0, legalMoves.size());
}

TEST(PawnTest, MoveOne) {
	MockBoard mockBoard;

	Pawn pawn = placePawn(WHITE, Position(0,0), mockBoard);
	std::vector<Position> legalMoves = pawn.getLegalMoves(mockBoard);
	EXPECT_EQ(1, legalMoves.size());
	EXPECT_EQ(Position(0,1), legalMoves.front());
}

TEST(PawnTest, MoveTwo) {
	MockBoard mockBoard;
	Position position;
	EXPECT_CALL(mockBoard, isPawnRow(position))
		.WillRepeatedly(Return(true));

	Pawn pawn = placePawn(WHITE, position, mockBoard);
	std::vector<Position> legalMoves = pawn.getLegalMoves(mockBoard);
	EXPECT_EQ(2, legalMoves.size());
}

// // Test that the pawn can move one ahead
// TEST(PawnTest, MoveAtA1) {
// 	Board board;
// 	board.clear();
// 	Position position;
// 	Pawn pawn(WHITE, position);
// 	board.placePiece(position, &pawn);
// 	std::vector<Position> legalMoves = pawn.getLegalMoves(&board);
// 	EXPECT_EQ(1, legalMoves.size());
// 	EXPECT_EQ(Position(0,1), legalMoves.front());
// }

// // Test that the pawn cannot move at the edge of the board
// TEST(PawnTest, MoveAtA8) {
// 	Board board;
// 	board.clear();
// 	Position position(0,7);
// 	Pawn pawn(WHITE, position);
// 	board.placePiece(position, &pawn);
// 	std::vector<Position> legalMoves = pawn.getLegalMoves(&board);
// 	EXPECT_EQ(0, legalMoves.size());
// }

// // Test that the pawn cannot move when the path is blocked
// TEST(PawnTest, MoveBlocked) {
// 	Board board;
// 	board.clear();

// 	Position position(0,0);
// 	Pawn pawn(WHITE, position);
// 	board.placePiece(position, &pawn);

// 	Position blockSquare = position.stepNorth();
// 	Pawn doublePawn(WHITE, blockSquare);
// 	board.placePiece(blockSquare, &doublePawn);

// 	std::vector<Position> legalMoves = pawn.getLegalMoves(&board);
// 	EXPECT_EQ(0, legalMoves.size());
// }

// TEST(PawnTest, CaptureOne) {
// 	Board board;
// 	board.clear();

// 	Position pawnPosition(0,1);
// 	Position enemyPosition = pawnPosition.stepNorthWest();

// 	Pawn pawn = placePawn(WHITE, pawnPosition, board);
// 	placePawn(BLACK, enemyPosition, board);

// 	std::vector<Position> legalMoves = pawn.getLegalMoves(&board);
// 	EXPECT_EQ(2, legalMoves.size());
// }

// TEST(PawnTest, CaptureTwo) {
// 	Board board;
// 	board.clear();

// 	Position pawnPosition(0,1);
// 	Position enemyPosition1 = pawnPosition.stepNorthWest();
// 	Position enemyPosition2 = pawnPosition.stepNorthEast();

// 	Pawn pawn = placePawn(WHITE, pawnPosition, board);
// 	placePawn(BLACK, enemyPosition1, board);
// 	placePawn(BLACK, enemyPosition2, board);

// 	std::vector<Position> legalMoves = pawn.getLegalMoves(&board);
// 	EXPECT_EQ(3, legalMoves.size());
// }

}