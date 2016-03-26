#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <vector>

bool Board::EmptyBoard(std::vector<int> &s, int board) {

	int x = Position::startingPosition[board];
	int i, j;


	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			const int pos = Position::getPosition(board, i, j);

			if (s[pos] != 0) {
				return false;
			}

		}
	}

	return true;
}

bool Board::TwoOnRow(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose) {

	int i, j;
	int count;

	for (i = 0; i < 3; ++i) {
		count = 0;
		for (j = 0; j < 3; ++j) {
			int position = Position::getPosition(board, i, j);
			if (macroboard[position] == player) {
				count++;
			}
			else {
				if (macroboard[position] == 0) {
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

bool Board::TwoOnColumn(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose) {

	int i, j;
	int count;

	for (j = 0; j < 3; ++j) {
		count = 0;
		for (i = 0; i < 3; ++i) {
			int position = Position::getPosition(board, i, j);
			if (macroboard[position] == player) {
				count++;
			}
			else {
				if (macroboard[position] == 0) {
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

bool Board::TwoOnFirstDiagonal(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose) {

	int position = Position::getPosition(board, 0, 0);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (macroboard[position + 10 * i] == player) {
			count++; 
		}
		else {
			if (macroboard[position + 10 * i] == 0) {
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

bool Board::TwoOnSecondDiagonal(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose) {

	int position = Position::getPosition(board, 0, 2);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (macroboard[position + 8*i] == player) {
			count++;
		}
		else {
			if (macroboard[position + 8 * i] == player) {
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

bool Board::CheckIfPlayerCanClose(const std::vector<int> &macroboard, const int board, const int player, std::pair<int, int> &PositionToClose) {

	if (TwoOnRow(macroboard, board, player, PositionToClose) == false && 
		TwoOnColumn(macroboard, board, player, PositionToClose) == false &&
		TwoOnFirstDiagonal(macroboard, board, player, PositionToClose) == false &&
		TwoOnSecondDiagonal(macroboard, board, player, PositionToClose) == false) {
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

std::vector<int> Board::empty_positions(std::vector<int> &s, int board) {

	int i, j;
	std::vector<int> empty_pos;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			int start = Position::getPosition(board, i, j);

			if (s[start] == 0) {
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
