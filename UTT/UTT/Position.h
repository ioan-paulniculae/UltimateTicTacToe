#pragma once

#include <vector>
class Position
{
public:
	
	static const std::vector<int> startingPosition;
	static int getPosition(const int board, const int i, const int j);
	static void setPosition(std::vector<int> &s, const int board, const int i, const int j, const int player);
};

