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

bool Board::twoOnRow(const int board, int player, std::pair<int, int> &PositionToClose) const {

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

bool Board::twoOnColumn(const int board, const int player, std::pair<int, int> &PositionToClose) const {

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

bool Board::twoOnFirstDiagonal(const int board, const int player, std::pair<int, int> &PositionToClose) const {

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

bool Board::twoOnSecondDiagonal(const int board, const int player, std::pair<int, int> &PositionToClose) const {

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

bool Board::getClosingPositions(const int board, const int player, std::pair<int, int> &PositionToClose) const {

	if (twoOnRow(board, player, PositionToClose) == false &&
		twoOnColumn(board, player, PositionToClose) == false &&
		twoOnFirstDiagonal(board, player, PositionToClose) == false &&
		twoOnSecondDiagonal(board, player, PositionToClose) == false) {
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

void Board::getEmptyPositions(const int board, std::vector<int> &emptyPositions){

	int i, j;
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			int start = Position::getPosition(board, i, j);

			if (_field[start] == 0) {
				emptyPositions.push_back(start);
			}
		}
	}
}

const int getCurrentPlayingBoards(const int board) {


}
Board::Board()
{
}


Board::~Board()
{
}
