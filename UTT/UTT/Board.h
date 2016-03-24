#pragma once
#include <string>
#include "Position.h"

class Board
{
	
public:
	int starting_position[] = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };
	bool is_empty_board(std::vector<int> &s, int board);
	bool board_to_close(std::vector<int> &s, int board, int player);
	int position_to_board(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);


	Board();
	~Board();
};

