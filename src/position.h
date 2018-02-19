/*
 * position.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Eirik Skogstad
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
  public:
    Position() : letter_(0), number_(0) {}
    Position(int letter, int number);

    bool operator==(const Position& other) const;

    int letter() const { return letter_; }
    int number() const { return number_; }
    int value()  const { if (number_ <= 4 && number_ >= 3) return 10; return 0; }

    // Functions for taking n=steps steps in a given direction.
    // myPosition.stepNorth() will return the position at one step north of
    // myPosition.
    Position stepNorth     (int steps = 1);
    Position stepNorthEast (int steps = 1);
    Position stepNorthWest (int steps = 1);
    Position stepSouth     (int steps = 1);
    Position stepSouthEast (int steps = 1);
    Position stepSouthWest (int steps = 1);
    Position stepEast      (int steps = 1);
    Position stepWest      (int steps = 1);

  private:
    int letter_;
    int number_;
};

#endif /* POSITION_H_ */
