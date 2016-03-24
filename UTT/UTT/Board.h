#pragma once
#include <string>
#include "Position.h"

class Board
{
	
public:
	int starting_position[] = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };
	bool EmptyBoard(std::vector<int> &s, int board);
	bool CanClose(std::vector<int> &s, int board, int player);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);


	Board();
	~Board();
};

