#pragma once
#include <vector>
class Board
{

public:
	Board(std::vector<int>& field, std::vector<int>& macroboard);

	bool isEmpty(const int board) const;
	bool getClosingPositions(const int board, const int player, std::pair<int, int> &PositionToClose) const;
	int getBoard(const int value) const;
	std::vector<int> getEmptyPositions(const int board);
	~Board();
private:
	std::vector<int>_fied;
	std::vector<int>_macroboard;
	bool twoOnRow(const int board, int player, std::pair<int, int> &PositionToClose) const;
	bool twoOnColumn(const int board, const int player, std::pair<int, int> &PositionToClose) const;
	bool twoOnFirstDiagonal(const int board, const int player, std::pair<int, int> &PositionToClose) const;
	bool twoOnSecondDiagonal(const int board, const int player, std::pair<int, int> &PositionToClose) const;

	Board();

};