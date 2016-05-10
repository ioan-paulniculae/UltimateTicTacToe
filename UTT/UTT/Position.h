#pragma once
#include <vector>
#include "Board.h"
class Position
{
public:
	static const std::vector<int> startingPosition;

	static std::pair<int, int> getRelativePosition(const int value);
	static std::pair<int, int> getRelativePosition(const std::pair<int, int> & move);
	static int absoluteToAbsolute(const std::pair<int, int > & move);

	static std::pair<int, int> getMatrixPosition(const int value);
	static std::pair<int, int> getMatrixPosition(const Board *b, const int board, const std::pair<int, int> relativePosition);
	static std::pair<int, int> getMatrixPosition(const Board *b, const int board, const int i, const int j);

	static int getBoard(const int value);

	static void getBoardPositions(const int board, std::vector<int> &boardPositions);
};

