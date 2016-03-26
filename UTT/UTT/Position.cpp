#include "stdafx.h"
#include "Position.h"
#include <cassert>

const std::vector<int> Position::startingPosition = { 0, 3, 6, 27, 30, 33, 54, 57, 60};

int Position::getPosition(const int board, const int i, const int j)
{

	assert(0 <= board && board < 9);
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);

	return startingPosition[board] + 9 * i + j % 3;
}

void Position::setPosition(std::vector<int>& macroboard,const int board, const int i, const int j, const int player)
{

	int position = getPosition(board, i, j);
	macroboard[position] = player;
}

std::pair<int, int> Position::getMatrixPosition(const int value) {

	assert(0 <= value && value <= 80);
	int x = value / 9;
	int y = value - 9 * x;
	return std::make_pair(x, y);

}

