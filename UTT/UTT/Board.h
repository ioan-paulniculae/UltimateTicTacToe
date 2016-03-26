#pragma once
#include <vector>
class Board
{
	 
public:
	Board(std::vector<int>& field, std::vector<int>& macroboard);
	bool EmptyBoard(const int board);
	bool CheckIfPlayerCanClose(std::pair<int,int> &PositionToClose, int board, int player);
	int PositionToBoard(int value);
	std::vector<int> empty_positions(int board);
	~Board();
private:
	std::vector<int>_fied;
	std::vector<int>_macroboard;
	bool TwoOnRow(std::pair<int, int> &PositionToClose, int board, int player);
	bool TwoOnColumn(std::pair<int,int> &PositionToClose, int board, int player);
	bool TwoOnFirstDiagonal(std::pair<int, int> &PositionToClose, int board, int player);
	bool TwoOnSecondDiagonal(std::pair<int,int> &PositionToClose, int board, int player);
	Board();

};