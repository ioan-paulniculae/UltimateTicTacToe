#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include <string>
#include <cassert>
#include <vector>
#include <set>
#include <random>



Board::Board()
{
	_field = std::vector<int>();
	_macroboard = std::vector<int>();
}

Board::Board(const std::vector<int>& field, const std::vector<int>& macroboard)
{
	_field = field;
	_macroboard = macroboard;
}

bool Board::isEmpty(const int board) const
{

	int x = Position::startingPosition[board];
	int i, j;
	int pos;

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			pos = getPosition(board, i, j);

			if (_field[pos] != 0) {
				return false;
			}
		}
	}

	return true;
}

bool Board::isClosed(const int board) const
{
	return !(Board::_macroboard[board] == 0 ||
		   Board::_macroboard[board] == -1);
}

void Board::addIfThree(const int player,
					   const int first,
					   const int second,
					   const int third,
					   std::vector<std::pair<int, int> >& positionToClose) const
{
	std::pair<int, int> closingPosition;
	if (_field[first] == 0 &&
		_field[second] == player &&
		_field[third] == player)
	{
		closingPosition = Position::getRelativePosition(first);
		positionToClose.push_back(closingPosition);
		return;
	}

	if (_field[first] == player &&
		_field[second] == 0&&
		_field[third] == player)
	{
		closingPosition = Position::getRelativePosition(second);//ai facut metoda aia sa imi zica pozitia relativa?
		//gen sa nu imi zica pozitia in matrice, ci boardu si i j? + am treaba la munca
		//fa metoda aia ca aia a dat crapau, lipsa ei,
		//trebe metoda care primeste un loc in matrice (ex 70) si zice
		//board 5 - x = 1; y = 2//ok? ok am inteles, refac functia
		// asta iti da perechea absoluta. de ce vreis i boardul  ? 

		positionToClose.push_back(closingPosition);
		return;
	}

	if (_field[first] == player &&
		_field[second] == player &&
		_field[third] == 0)
	{
		closingPosition = Position::getRelativePosition(third);
		positionToClose.push_back(closingPosition);
		return;
	}
}

void Board::twoOnRow(const int board,
					 const int player,
					 const int row,
					 std::vector< std::pair<int, int> > &PositionToClose) const
{
	int first = getPosition(board, row, 0);
	int second = getPosition(board, row, 1);
	int third = getPosition(board, row, 2);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnColumn(const int board,
						const int player,
						const int column,
						std::vector< std::pair<int, int> > &PositionToClose) const
{

	int first = getPosition(board, 0, column);
	int second = getPosition(board, 1, column);
	int third = getPosition(board, 2, column);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnFirstDiagonal(const int board,
							   const int player,
							   std::vector< std::pair<int, int> > &PositionToClose) const
{

	int first = getPosition(board, 0, 0);
	int second = getPosition(board, 1, 1);
	int third = getPosition(board, 2, 2);

	addIfThree(player, first, second, third, PositionToClose);
}

void Board::twoOnSecondDiagonal(const int board,
								const int player,
								std::vector< std::pair<int, int> > &PositionToClose) const
{

	int first = getPosition(board, 0, 2);
	int second = getPosition(board, 1, 1);
	int third = getPosition(board, 2, 0);

	addIfThree(player, first, second, third, PositionToClose);
}

bool Board::getClosingPositions(const int board,
								const int player,
								std::set< std::pair<int, int> > &allPositionsToClose) const{

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

int Board::getPosition(const int board, const int i, const int j) const
{

	assert(0 <= board && board < 9);
	assert(0 <= i && i < 3);
	assert(0 <= j && j < 3);

	return Position::startingPosition[board] + 9 * i + j % 3;
}

void Board::setPosition(const int board, const int i, const int j, const int player)
{

	int position = getPosition(board, i, j);
	_macroboard[position] = player;
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



int Board::next(const std::pair<int, int>& move) const
{
	return next(move.first, move.second);
}

int Board::next(const int i, const int j) const
{
	assert(i >= 0);
	assert(i < 3);

	assert(j >= 0);
	assert(j < 3);

	int nextBoard = 3 * i + j;

	return isClosed(nextBoard) ? -1 : nextBoard;
}


void Board::getEmptyPositions(const int board, std::set<std::pair<int, int> > &emptyPositions) const
{

	int i, j;
	int start;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {

			start = getPosition(board, i, j);

			if (_field[start] == 0) {
				emptyPositions.insert(std::make_pair(i, j));
			}
		}
	}
}

void Board::getCurrentPlayingBoards(std::vector<int> &playingBoards){

	for (int i = 0; i < 9; ++i) {
		if (_macroboard[i] == -1)
		{
			playingBoards.push_back(i);
		}
	}

}

bool Board::throwOpponentNoAdvantage(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions) {

	assert(0 <= board && board < 9);
	assert(1 <= opponent && opponent <= 2);

	int newboard;
	std::set<std::pair<int, int> > emptyPositions;
	std::set< std::pair <int, int> > closingPositions;

	getEmptyPositions(board, emptyPositions);

	for (auto& emptyPos : emptyPositions)
	{

		newboard = next(emptyPos);

		if (newboard == -1)
		{
			newboard = 3 * emptyPos.first + emptyPos.second; //nu tratam cazul in care mutarea il trimite in mai multe jocuri
		}
		if ((_macroboard[newboard] == 0  ||
			 _macroboard[newboard] == -1 )//daca il trimit intr-un joc disponimbil
			&&!getClosingPositions(newboard, opponent, closingPositions))
		{
			possibleClosingPossitions.push_back(Position::getMatrixPosition(this, board, emptyPos));
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
bool Board::throwOpponentInBlankGame(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions)
{
	assert(0 <= board && board < 9);
	assert(1 <= opponent && opponent <= 2);

	int newboard;
	std::set<std::pair<int, int> > emptyPositions;
	std::set< std::pair <int, int> > closingPositions;

	getEmptyPositions(board, emptyPositions);

	for (auto& emptyPos : emptyPositions)
	{
		// complematam cu metoda paul
		newboard = 3 * emptyPos.first + emptyPos.second;
		if (_macroboard[newboard] == 0 &&
			isEmpty(newboard) == true)
		{
			if (board == newboard)
			{
				continue;
			}
			else
			{
				possibleClosingPossitions.push_back(Position::getMatrixPosition(this, board, emptyPos));
			}
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

bool Board::playingBoards(const int move) const
{
	int board = Board::getBoard(move);
	std::set<std::pair<int, int> > emptyPositions;

	if (_macroboard[board] == 0)
	{
		getEmptyPositions(board, emptyPositions);

		if (emptyPositions.size())
		{ 
			return true;
		}
	}

	if (_macroboard[board] == -1)
	{
		return true;
	}

	return false;
}

bool Board::isValid(const int move) const {

	if (_field[move] == 0)
	{
		if (playingBoards(move))
		{
			return true;
		}
	}

	return false;
}

void Board::getEmptyPositions(std::set<std::pair<int,int> > &emptyPositions) const
{
	int i;
	int j;
	std::pair<int,int> relativePosition;
	std::set<std::pair<int, int> > positions;
	std::set<std::pair<int, int> >::iterator position;
	for (i = 0; i < 9; i++)
	{
		if (playingBoards(getPosition(i, 0, 0)))
		{
			getEmptyPositions(i, positions);
			for (j = 0; j < positions.size(); j++)
			{
				position = positions.begin();
				std::advance(position, j);
				relativePosition = Position::getMatrixPosition(this, i, *position);
				emptyPositions.insert( relativePosition );
			}

			positions.clear();
		}
	}
}

std::pair<int, int> Board::chooseBestPosition(std::pair<int, int> bestPosition, std::vector< std::pair<int,int> > blankPositions) 
{

	////send opponent in a blank game 
	//for (auto& blankPos : blankPositions) 
	//{
	//	if (bestPosition == blankPos) 
	//	{
	//		return blankPos;//:)) cine a scris asta? eu si alex tu cine?theo:))
	//	}
	//}
	//return std::make_pair(0, 0);
	return *blankPositions.begin();
}

Board::~Board()
{
	_field.clear();
	_macroboard.clear();
}
