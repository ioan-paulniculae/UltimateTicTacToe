#include "stdafx.h"
#include "Position.h"
#include "Board.h"
#include <cassert>

const std::vector<int> Position::startingPosition = { 0, 3, 6, 27, 30, 33, 54, 57, 60};


std::pair<int, int> Position::getRelativePosition(const int value)
{
	assert(0 <= value && value <= 80);
	int x = value % 3;
	int y = value / 9 % 3;
	return std::make_pair(y, x);
}

std::pair<int, int> Position::getRelativePosition(const std::pair<int, int> & move) {

	return std::make_pair(move.first % 3, move.second % 3);
}
int Position::absoluteToAbsolute(const std::pair<int, int>& move)
{
	return move.second * 9 + move.first;
}
std::pair<int, int> Position::getMatrixPosition(const int value) {

	assert(0 <= value && value <= 80);
	int x = value / 9;
	int y = value % 9;
	return std::make_pair(y, x);

}

std::pair<int, int> Position::getMatrixPosition(const Board *b, const int board, const std::pair<int, int> relativePosition) {

	int position = b->getPosition(board, relativePosition.first, relativePosition.second);
	int x = position / 9;
	int y = position % 9;
	return std::make_pair(y, x);

}

