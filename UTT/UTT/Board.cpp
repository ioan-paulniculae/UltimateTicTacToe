#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <vector>

bool Board::EmptyBoard(std::vector<int> &s, int board) {

	int x = starting_position[board];
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


bool Board::CanClose(std::vector<int> &s, int board, int player) {

	int x = starting_position[board];
	int i, j;
	int count;


	for (i = 0; i < 3; ++i) {
		count = 0;
		for (j = 0; j < 3; ++j) {


			int pos = Position::getPosition(board, i, j);

			if (s[pos] == player) {
				count++;
			}
		}
		if (count == 2)
			return true;
	}


	for (j = 0; j < 3; ++j) {
		count = 0;
		for (i = 0; i < 3; ++i) {

			Position x;
			int pos = Position::getPosition(board, i, j);

			if (s[pos] == player) {
				count++;
			}
		}
		if (count == 2)
			return true;
	}

	int posdiag1 = Position::getPosition(board, 0, 0);
	count = 0;

	for (int i = 0; i < 3; ++i) {

		if (s[posdiag1 + 10 * i]  == player) {
			count++;
		}
	}

	if (count == 2)
		return true;

	int posdiag2 = Position::getPosition(board, 0, 2);
	count = 0;

	for (int i = 0; i < 3; ++i) {

		if (s[posdiag1 + 8 * i] == player) {
			count++;
		}
	}

	if (count == 2)
		return true;

	return false;
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
