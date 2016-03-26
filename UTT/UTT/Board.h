#pragma once
#include <string>

class Board
{
	 
public:
	bool EmptyBoard(std::vector<int> &s, int board);
	bool CheckIfPlayerCanClose(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);
	Board();
	~Board();
private:
	bool TwoOnRow(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose);
	bool TwoOnColumn(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose);
	bool TwoOnFirstDiagonal(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose);
	bool TwoOnSecondDiagonal(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose);
};

