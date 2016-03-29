#include "stdafx.h"
#include "Position.h"
#include "Board.h"
#include <cassert>

const std::vector<int> Position::startingPosition = { 0, 3, 6, 27, 30, 33, 54, 57, 60};

int Position::getPosition(const int board, const int i, const int j)
{

	assert(0 <= board && board < 9);
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);

	return startingPosition[board] + 9 * i + j % 3;
}

void Position::setPosition(const int board, const int i, const int j, const int player)
{

	int position = getPosition(board, i, j);
	Board::_macroboard[position] = player;
}

std::pair<int, int> Position::getRelativePosition(const int value)
{
	int x = value % 3;
	int y = value / 9 % 3;
	return std::make_pair(x, y);
}

std::pair<int, int> Position::getMatrixPosition(const int value) {

	assert(0 <= value && value <= 80);
	int x = value / 9;
	int y = value - 9 * x;
	return std::make_pair(y, x);

}

int Position::nextBoard(const std::pair<int, int>& move)
{
	return nextBoard(move.first, move.second);
}

int Position::nextBoard(const int i, const int j)
{
	assert(i >= 0);
	assert(i < 3);

	assert(j >= 0);
	assert(j < 3);

	int nextBoard = 3 * i + j;

	return Board::isClosed(nextBoard)? -1 : nextBoard;
}

std::pair<int, int> Position::getMatrixPosition(const int board, const std::pair<int, int> relativePosition) {

	int position = getPosition(board, relativePosition.first, relativePosition.second);
	int x = position / 9;
	int y = position - 9 * x;
	return std::make_pair(y, x);

}

