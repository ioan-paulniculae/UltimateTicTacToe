#pragma once
#include <vector>
class Position
{
public:
	static const std::vector<int> startingPosition;
	static int getPosition(const int board, const int i, const int j);
	static void setPosition(const int board, const int i, const int j, const int player);
	static std::pair<int, int> getRelativePosition(const int value);
	static std::pair<int, int> getMatrixPosition(const int value);
	static std::pair<int, int> getMatrixPosition(const int board, const std::pair<int, int> relativePosition);
	static std::pair<int, int> getMatrixPosition(const int board, const int i, const int j);


	static int nextBoard(const std::pair<int, int>& move);
	static int nextBoard(const int i, const int j);
};

