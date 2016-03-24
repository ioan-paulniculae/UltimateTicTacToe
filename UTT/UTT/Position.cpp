#include "stdafx.h"
#include "Position.h"
#include <cassert>



int Position::GetPosition(int board, int i, int j)const {

	assert(0 <= board && board < 9);
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);

	return starting_position[board] + 9 * i + j % 3;
}

void Position::SetPosition(std::vector<int> &s, int board, int i, int j, int player) {

	int position = Position::GetPosition(board, i, j);

	s[position] = player;
}


Position::Position()
{	
}

Position::~Position()
{
}
