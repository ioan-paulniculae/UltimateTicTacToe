#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <vector>

Board::Board(std::vector<int>& field, std::vector<int>& macroboard)
{
	_fied = field;
	_macroboard = macroboard;
}

bool Board::EmptyBoard(int board) {

	int x = Position::startingPosition[board];
	int i, j;
	int pos;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			pos = Position::getPosition(board, i, j);

			if (_macroboard[pos] != 0) {
				return false;
			}

		}
	}

	return true;
}

bool Board::TwoOnRow(std::pair<int, int> &PositionToClose, int board, int player) {

	int i, j;
	int count;
	int position;

	for (i = 0; i < 3; ++i) {
		count = 0;
		for (j = 0; j < 3; ++j) {
			position = Position::getPosition(board, i, j);
			if (_macroboard[position] == player) {
				count++;
			}
			else {
				if (_macroboard[position] == 0) {
					PositionToClose.first = i;
					PositionToClose.second = j;
				}
			}
		}
		if (count == 2) {
			return true;
		}
	}
	PositionToClose.first = -1;
	PositionToClose.second = -1;
	return false;
}

bool Board::TwoOnColumn(std::pair<int, int> &PositionToClose, int board, int player) {

	int i, j;
	int count;

	for (j = 0; j < 3; ++j) {
		count = 0;
		for (i = 0; i < 3; ++i) {
			int position = Position::getPosition(board, i, j);
			if (_macroboard[position] == player) {
				count++;
			}
			else {
				if (_macroboard[position] == 0) {
					PositionToClose.first = i;
					PositionToClose.second = j;
				}
			}
		}
		if (count == 2) {
			return true;
		}
	}
	PositionToClose.first = -1;
	PositionToClose.second = -1;
	return false;
}

bool Board::TwoOnFirstDiagonal(std::pair<int, int> &PositionToClose, int board, int player) {

	int position = Position::getPosition(board, 0, 0);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (_macroboard[position + 10 * i] == player) {
			count++; 
		}
		else {
			if (_macroboard[position + 10 * i] == 0) {
				PositionToClose.first = i;
				PositionToClose.second = i;
			}
		}
	}

	if (count == 2) {
		return true; 
	}
	else {
		PositionToClose.first = -1;
		PositionToClose.second = -1;
		return false;
	}
}

bool Board::TwoOnSecondDiagonal(std::pair<int,int> &PositionToClose, int board, int player) {

	int position = Position::getPosition(board, 0, 2);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (_macroboard[position + 8 * i] == player) {
			count++;
		}
		else {
			if (_macroboard[position + 8 * i] == player) {
				if (i == 0) {
					PositionToClose.first = i;
					PositionToClose.second = 2;
				}
				if (i == 1) {
					PositionToClose.first = i;
					PositionToClose.second = i;
				}
				if (i == 2) {
					PositionToClose.first = i;
					PositionToClose.second = 0;
				}
				
			}
		}
	}

	if (count == 2) {
		return true;
	}
	else {
		PositionToClose.first = -1;
		PositionToClose.second = -1;
		return false;
	}
}

bool Board::CheckIfPlayerCanClose(std::pair<int,int> &PositionToClose, int board, int player) {

	if (TwoOnRow(PositionToClose, board, player) == false && 
		TwoOnColumn(PositionToClose, board, player) == false && 
		TwoOnFirstDiagonal(PositionToClose, board, player) == false && 
		TwoOnSecondDiagonal(PositionToClose, board, player) == false) {
			return false;
	}

	return true;

}

int Board::PositionToBoard(int value) {

	int line = value / 9;
	int col = value % 9;

	int i, j;
	int number = 0;

	for (i = 0; i < 3; ++i) {
		if (3 * i <= line && line < 3 * i + 3)
			number = 3 * i;
	}

	for (j = 0; j < 3; ++j) {
		if (3 * j <= col && col < 3 * j + 3)
			number += j;
	}

	return number;
}

std::vector<int> Board::empty_positions(int board) {

	int i, j;
	std::vector<int> empty_pos;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			int start = Position::getPosition(board, i, j);

			if (_macroboard[start] == 0) {
				empty_pos.push_back(start);
			}
		}
	}

	return empty_pos;
}

Board::Board()
{
}


Board::~Board()
{
}
