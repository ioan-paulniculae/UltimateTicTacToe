#pragma once
#include <string>

class Board
{
	
public:
	bool EmptyBoard(std::vector<int> &s, int board);
	bool CanClose(std::vector<int> &s, int board, int player);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);

private:
	bool TwoOnFirstDiagonal();//toDO: add arguments and use it in CanCLose Method
	Board();
	~Board();
};

