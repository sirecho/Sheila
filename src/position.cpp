/*
 * position.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: Eirik Skogstad
 */

#include "position.h"

Position::Position(int letter, int number) {
	letter_ = letter;
	number_ = number;
}

bool Position::operator==(const Position& other) const {
	return letter() == other.letter() && 
		   number() == other.number();
}

Position Position::stepNorth(int steps) {
	return Position(letter_, number_+steps);
}

Position Position::stepSouth(int steps) {
	return Position(letter_, number_-steps);
}

Position Position::stepEast(int steps) {
	return Position(letter_+steps, number_);
}

Position Position::stepWest(int steps) {
	return Position(letter_-steps, number_);
}

Position Position::stepNorthEast(int steps) {
	return Position(letter_+steps, number_+steps);
}

Position Position::stepNorthWest(int steps) {
	return Position(letter_-steps, number_+steps);
}

Position Position::stepSouthEast(int steps) {
	return Position(letter_+steps, number_-steps);
}

Position Position::stepSouthWest(int steps) {
	return Position(letter_-steps, number_-steps);
}