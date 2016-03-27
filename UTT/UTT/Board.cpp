#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <cassert>
#include <vector>
#include <set>
#include <ctime>

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

void Board::addIfThree(const int player, const int first, const int second, const int third, std::vector<std::pair<int, int> >& positionToClose) const
{
	std::pair<int, int> closingPosition;
	if (!(_field[first] == player) &&
		(_field[second] == player) &&
		(_field[third] == player))
	{
		closingPosition = Position::getMatrixPosition(first);
		positionToClose.push_back(closingPosition);
		return;
	}

	if ((_field[first] == player) &&
		!(_field[second] == player) &&
		(_field[third] == player))
	{
		closingPosition = Position::getMatrixPosition(second);
		positionToClose.push_back(closingPosition);
		return;
	}

	if ((_field[first] == player) &&
		(_field[second] == player) &&
		!(_field[third] == player))
	{
		closingPosition = Position::getMatrixPosition(third);
		positionToClose.push_back(closingPosition);
		return;
	}
}

void Board::twoOnRow(const int board, const int player, const int row, std::vector< std::pair<int, int> > &PositionToClose) const {

	int first = Position::getPosition(board, row, 0);
	int second = Position::getPosition(board, row, 1);
	int third = Position::getPosition(board, row, 2);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnColumn(const int board, const int player, const int column, std::vector< std::pair<int, int> > &PositionToClose) const {

	int first = Position::getPosition(board, 0, column);
	int second = Position::getPosition(board, 1, column);
	int third = Position::getPosition(board, 2, column);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {
	int first = Position::getPosition(board, 0, 0);
	int second = Position::getPosition(board, 1, 1);
	int third = Position::getPosition(board, 2, 2);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const {

	int first = Position::getPosition(board, 0, 2);
	int second = Position::getPosition(board, 1, 1);
	int third = Position::getPosition(board, 2, 0);

	addIfThree(player, first, second, third, PositionToClose);

}

bool Board::getClosingPositions(const int board,
								const int player,
								std::set< std::pair<int, int> > &allPositionsToClose) const {

	if (_macroboard[board] != 0)
	{
		return false;
	}
	std::vector< std::pair<int, int> > PositionToClose;

	twoOnRow(board, player, 0, PositionToClose);
	twoOnRow(board, player, 1, PositionToClose);
	twoOnRow(board, player, 2, PositionToClose);

	twoOnColumn(board, player, 0, PositionToClose);
	twoOnColumn(board, player, 1, PositionToClose);
	twoOnColumn(board, player, 2, PositionToClose);

	twoOnFirstDiagonal(board, player, PositionToClose);
	twoOnSecondDiagonal(board, player, PositionToClose);

	allPositionsToClose.insert(PositionToClose.begin(), PositionToClose.end());
	if (allPositionsToClose.size()) {
		return true;
	}

	return false;
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

void Board::getEmptyPositions(const int board, std::vector<std::pair<int, int> > &emptyPositions) const{

	int i, j;
	int start;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			start = Position::getPosition(board, i, j);

			if (_field[start] == 0) {
				emptyPositions.push_back(std::make_pair(i, j));
			}
		}
	}
}

void Board::getCurrentPlayingBoards(std::vector<int> &playingBoards) const{

	for (int i = 0; i < 9; ++i) {
		if (_macroboard[i] == -1)
		{
			playingBoards.push_back(i);
		}
	}

}

bool Board::throwOpponentNoAdvantage(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions) const {

	assert(0 <= board && board < 9);
	assert(1 <= opponent && opponent <= 2);

	int newboard;
	std::vector<std::pair<int, int> > emptyPositions;
	std::set< std::pair <int, int> > closingPositions;
	
	//getCurrentPlayingBoards(getPlayingBoards);
	getEmptyPositions(board, emptyPositions);

	for (auto& emptyPos : emptyPositions)
	{
		// complematam cu metoda paul
		newboard = 3 * emptyPos.first + emptyPos.second;
		if (_macroboard[newboard] == 0 &&
			!getClosingPositions(newboard, opponent, closingPositions))
		{
			possibleClosingPossitions.push_back(Position::getMatrixPosition(board, emptyPos));
		}
		else
		{
			closingPositions.clear();
		}
	}
	if (possibleClosingPossitions.size())
	{
		return true;
	}
	return false;

}

Board::Board()
{
}


Board::~Board()
{
}
