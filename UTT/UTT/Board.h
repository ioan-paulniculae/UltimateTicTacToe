#pragma once
#include <string>

class Board
{
	
public:
	bool EmptyBoard(std::vector<int> &s, int board);
	bool CheckIfPlayerCanClose(std::vector<int> &s, int board, int player);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);

private:
	bool TwoOnRow(std::vector<int> &s, int board, int player);
	bool TwoOnColumn(std::vector<int> &s, int board, int player);
	bool TwoOnFirstDiagonal(std::vector<int> &s, int board, int player);
	bool TwoOnSecondDiagonal(std::vector<int> &s, int board, int player);
	Board();
	~Board();
};

