#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <vector>
#include <set>

Board::Board(std::vector<int>& field, std::vector<int>& macroboard)
{
	_field = field;
	_macroboard = macroboard;
}

bool Board::isEmpty(const int board) const {

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

bool Board::twoOnRow(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {

	int i, j;
	int count;
	int position;

	for (i = 0; i < 3; ++i) {
		count = 0;
		for (j = 0; j < 3; ++j) {
			position = Position::getPosition(board, i, j);
			if (_field[position] == player) {
				count++;
			}
		}
		if (count == 2) {
			for (j = 0; j < 3; j++) {
				position = Position::getPosition(board, i, j);
				if (_field[position] == 0) {
					PositionToClose.push_back(std::make_pair(i, j));
				}
			}
		}
	}

	if (PositionToClose.size() == 0) {
		PositionToClose.push_back(std::make_pair(-1, -1));
		return false;
	}

	return true;
}

bool Board::twoOnColumn(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {

	int i, j;
	int count;
	int position;

	for (j = 0; j < 3; ++j) {
		count = 0;
		for (i = 0; i < 3; ++i) {
			int position = Position::getPosition(board, i, j);
			if (_field[position] == player) {
				count++;
			}
		}
		if (count == 2) {
			for (i = 0; i < 3; i++) {
				position = Position::getPosition(board, i, j);
				if (_field[position] == 0) {
					PositionToClose.push_back(std::make_pair(i, j));
				}
			}
		}
	}

	if (PositionToClose.size() == 0) {
		PositionToClose.push_back(std::make_pair(-1, -1));
		return false;
	}

	return true;
}

bool Board::twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {

	int position = Position::getPosition(board, 0, 0);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (_field[position + 10 * i] == player) {
			count++; 
		}
		else {
			if (_field[position + 10 * i] == 0) {
				PositionToClose.push_back(std::make_pair(i, i));
			}
		}
	}

	if (count == 2) {
		return true; 
	}

	PositionToClose.push_back(std::make_pair(-1, -1));

	return false;
}

bool Board::twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {

	int position = Position::getPosition(board, 0, 2);
	int count = 0;

	for (int i = 0; i < 3; ++i) {
		if (_field[position + 8 * i] == player) {
			count++;
		}
		else {
			if (_field[position + 8 * i] == 0) {
				if (i == 0) {
					PositionToClose.push_back(std::make_pair(i, 2));
				}
				if (i == 1) {
					PositionToClose.push_back(std::make_pair(i, i));
				}
				if (i == 2) {
					PositionToClose.push_back(std::make_pair(i, 0));
				}	
			}
		}
	}

	if (count == 2) {
		return true;
	}

	PositionToClose.push_back(std::make_pair(-1, -1));

	return false;
}

bool Board::getClosingPositions(const int board,
								const int player,
								std::set< std::pair<int, int> > &allPositionsToClose) const {

	std::vector< std::pair<int, int> > PositionToClose;

	if (twoOnRow(board, player, PositionToClose)) {
		allPositionsToClose.insert(PositionToClose.begin(), PositionToClose.end());
	}

	if (twoOnColumn(board, player, PositionToClose)) {
		allPositionsToClose.insert(PositionToClose.begin(), PositionToClose.end());
	}

	if (twoOnFirstDiagonal(board, player, PositionToClose)) {
		allPositionsToClose.insert(PositionToClose.begin(), PositionToClose.end());
	}

	if (twoOnSecondDiagonal(board, player, PositionToClose)) {
		allPositionsToClose.insert(PositionToClose.begin(), PositionToClose.end());
	}

	bool cannotClose = !twoOnRow(board, player, PositionToClose) &&
		!twoOnColumn(board, player, PositionToClose) &&
		!twoOnFirstDiagonal(board, player, PositionToClose) &&
		!twoOnSecondDiagonal(board, player, PositionToClose);

	if (cannotClose) {
		return false;
	}

	return true;
}

int Board::getBoard(const int value) const{

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

std::vector<int> Board::getEmptyPositions(const int board) {

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
