#pragma once
#include <string>

class Board
{
	 
public:
	bool EmptyBoard(std::vector<int> &s, int board);
	bool CheckIfPlayerCanClose(std::pair<int,int> &PositionToClose, std::vector<int> &s, int board, int player);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(std::vector<int> &s, int board);
	Board();
	~Board();
private:
	bool TwoOnRow(std::pair<int, int> &PositionToClose, std::vector<int> &s, int board, int player);
	bool TwoOnColumn(std::pair<int,int> &PositionToClose, std::vector<int> &s, int board, int player);
	bool TwoOnFirstDiagonal(std::pair<int, int> &PositionToClose, std::vector<int> &s, int board, int player);
	bool TwoOnSecondDiagonal(std::pair<int,int> &PositionToClose, std::vector<int> &s, int board, int player);

};

