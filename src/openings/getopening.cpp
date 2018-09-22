/*
 * getopening.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Eirik Skogstad
 */

#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdint>
#include<unordered_map>

using namespace std;

struct BookEntry {
	uint16_t move;
	uint16_t weight;
	uint32_t learn;
};

class PolyGlotBookReader {
public:
	PolyGlotBookReader() {

	}

	void find_move(Board *board) {
		
	}

	void get_position(uint16_t move) {
		int mask = 0b00000111;
		int to_file   = move & mask;
		int to_row    = move >> 3 & mask;
		int from_file = move >> 6 & mask;
		int from_row  = move >> 9 & mask;
		int promotion = move >> 12;

		Position from = Position(from_file, from_row);
		Position to = Position(to_file, to_row);
		Piece *piece = board->pieceAt(from);
		piece->move(board, to);
	}
}



int main() {
	unordered_map<uint64_t, BookEntry> hashtable;

	ifstream book("ProDeo.bin", ios::binary);

	int size = 16;
    unsigned char entry[size];

    book.seekg (0, ios::beg);

    while (book) {
	    book.read ((char*) entry, size);

		uint64_t    key = (uint64_t)  entry[0] << 56 |
						  (uint64_t)  entry[1] << 48 |
						  (uint64_t)  entry[2] << 40 |
						  (uint64_t)  entry[3] << 32 |
						  (uint64_t)  entry[4] << 24 |
						  (uint64_t)  entry[5] << 16 |
						  (uint64_t)  entry[6] <<  8 |
						  (uint64_t)  entry[7];

		uint16_t   move = (uint16_t)  entry[8] <<  8 | 
						  (uint16_t)  entry[9];

		uint16_t weight = (uint16_t) entry[10] <<  8 | 
						  (uint16_t) entry[11];

		uint32_t  learn = (uint16_t) entry[12] << 24 | 
						  (uint16_t) entry[13] << 16 | 
						  (uint16_t) entry[14] <<  8 | 
						  (uint16_t) entry[15];

		hashtable.insert(make_pair(key, BookEntry{move, weight, learn}));
	}

	book.close();
}