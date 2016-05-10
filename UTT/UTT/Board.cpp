#include "stdafx.h"
#include "Board.h"
#include "Position.h"
#include "Utility.h"
#include <string>
#include <cassert>
#include <vector>
#include <set>
#include <random>



Board::Board()
{
	_field = std::vector<int>(81, 0);
	_macroboard = std::vector<int>(9, 0);
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

bool Board::gameIsFinished(const int player) const
{
	bool firstDiagonal = _macroboard[0] == player && _macroboard[4] == player && _macroboard[8] == player;
	bool secondDiagonal = _macroboard[2] == player && _macroboard[4] == player && _macroboard[6] == player;
	bool firstColumn = _macroboard[0] == player && _macroboard[3] == player && _macroboard[6] == player;
	bool secondColumn = _macroboard[1] == player && _macroboard[4] == player && _macroboard[7] == player;
	bool thirdColumn = _macroboard[2] == player && _macroboard[5] == player && _macroboard[8] == player;
	bool firstRow = _macroboard[0] == player && _macroboard[1] == player && _macroboard[2] == player;
	bool secondRow = _macroboard[3] == player && _macroboard[4] == player && _macroboard[5] == player;
	bool thirdRow = _macroboard[6] == player && _macroboard[7] == player && _macroboard[8] == player;

	return firstDiagonal || secondDiagonal || firstColumn || secondColumn || thirdColumn || firstRow || secondRow || thirdRow;
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

void Board::updateMacroboard(const std::pair<int, int>& move)
{
	for (int i = 0; i < 9; ++i) {
		if (_macroboard[i] == -1) {
			_macroboard[i] = 0;
		}
	}

	int nextBoard = next(move);
	bool allFlag = false;
	if (nextBoard != -1) {
		if (_macroboard[nextBoard]) {
			allFlag = true;
		}
		else {
			if (isFinished(nextBoard)) {
				allFlag = true; //  cred
			}
		}
	}
	else
	{
		allFlag = true;
	}

	if (allFlag)
	{
		for (int b = 0; b < 9; b++)
		{
			if (_macroboard[b] == 0)
			{
				if (!isFinished(b))
				{
					_macroboard[b] = -1;
				}
			}
		}
	}
	else
	{
		_macroboard[nextBoard] = -1;
	}

}

bool Board::hasTwoOnARow(const int player, const int first, const int second, const int third) const
{
	if (_macroboard[first] == player &&
		_macroboard[second] == player)
	{
		if (_macroboard[third] == 0 &&
			!isFinished(third))
		{
			return true;
		}
	}
	return false;
}

bool Board::checkConfiguration(const int player, const int first, const int second, const int third, std::vector<int>& weights) const
{
	if (hasTwoOnARow(player, first, second, third))
	{
		weights[third]++;
		return true;
	}
	else
	{
		if (hasTwoOnARow(player, first, third, second))
		{
			weights[second]++;
			return true;

		}
		else
		{
			if (hasTwoOnARow(player, second, third, first))
			{
				weights[first]++;
				return true;

			}
		}
	}

	return false;
}

bool Board::scanMacroboardForTwo(const int player, std::vector<int>& weights) const
{
	bool result = false;
	result = result ||
			 checkConfiguration(player, 0, 1, 2, weights) ||
			 checkConfiguration(player, 3, 4, 5, weights) ||
			 checkConfiguration(player, 6, 7, 8, weights) ||

			 checkConfiguration(player, 0, 3, 6, weights) ||
			 checkConfiguration(player, 1, 4, 7, weights) ||
			 checkConfiguration(player, 2, 5, 8, weights) ||

			 checkConfiguration(player, 0, 5, 8, weights) ||
			 checkConfiguration(player, 3, 5, 7, weights);
	return result;
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



int Board::eval(const int player) const
{
	if (gameIsFinished(player))
	{
		return INF;
	}
	if (gameIsFinished(UTTT::Core::Utility::getNextPlayer(player)))
	{
		return -INF;
	}

	unsigned short opponentPlayingBoards = 0;
	int score = 0;

	std::vector<int> cellWeight(9, 1);

	if (scanMacroboardForTwo(player, cellWeight)) //avem cel putin o configuratie de 2 consecutive
	{
		score += 100;
	}
	if (scanMacroboardForTwo(UTTT::Core::Utility::getNextPlayer(player), cellWeight))//oponentul are cel putin o configuratie de 2 consecutive
	{
		score -= 75;
	}

	for (int i = 0; i < 9; i++)
	{
		if (_macroboard[i] == player)
		{
			score += 10;
		}
		if (_macroboard[i] == UTTT::Core::Utility::getNextPlayer(player))
		{
			score -= 10;
		}
		if (_macroboard[i] == 0 &&
			!isFinished(i))
		{
			score += cellWeight[i] * (boardEval(i, player) - boardEval(i, UTTT::Core::Utility::getNextPlayer(player)));
		}
		if (_macroboard[i] == -1)
		{
			opponentPlayingBoards++;
		}
	}
	//daca oponentul poate juca doar intr-un singur minigame, nu afectam cu nimic scorul
	//altfel scadem scalat cu numarul de boarduri in care se poate misca din scor
	//pentru a considera o mutare care da mana libera adversarului, mai slaba decat altele
	score -= (opponentPlayingBoards - 1) * 5;

	return score;
}

int Board::boardEval(const int board, const int player) const
{
	int id = 0;
	int number, i, j;
	bool ok;
	int score = 0;
	if (finishes(move, player, id))
	{
		score += 5 * multiplier;
		if (board == 4)
		{
			score += 10 * multiplier;
		}
		else if (board == 0 ||
			board == 2 ||
			board == 6 ||
			board == 8)
		{
			score += 3 * multiplier;
		}
	}

	std::pair<int, int> pair = Position::getRelativePosition(move);
	if (pair.first == 1 && pair.second == 1)
	{
		score += 3 * multiplier;
	}
	if (board == 4)
	{
		score += 3 * multiplier;
	}

	// rows
	for (i = 0; i < 3; i++)
	{
		number = 0;
		ok = true;
		for (j = 0; j < 3; ++j) {
			if (_macroboard[3 * i + j] == player) {
				number++;
			}
			if (_macroboard[3 * i + j] == opponent) {
				ok = false;
			}
		}
		if (ok == true && number == 2) {
			score += 4 * multiplier;
		}
	}


	// columns
	for (i = 0; i < 3; i++)
	{
		number = 0;
		ok = true;
		for (j = 0; j < 3; ++j) {
			if (_macroboard[i + 3 * j] == player) {
				number++;
			}
			if (_macroboard[i + 3 * j] == opponent) {
				ok = false;
			}
		}
		if (ok == true && number == 2) {
			score += 4 * multiplier;
		}
	}


	// 1st diagonal
	number = 0;
	ok = true;
	for (i = 0; i < 9; i += 4) {
		if (_macroboard[i] == player) {
			number++;
		}
		if (_macroboard[i] == opponent) {
			ok = false;
		}
	}
	if (ok == true && number == 2) {
		score += 4 * multiplier;
	}

	// 2nd diagonal
	number = 0;
	ok = true;
	for (i = 2; i < 7; i += 2) {
		if (_macroboard[i] == player) {
			number++;
		}
		if (_macroboard[i] == opponent) {
			ok = false;
		}
	}
	if (ok == true && number == 2) {
		score += 4 * multiplier;
	}

	//pentru boardurile mici
	std::set<std::pair<int, int>> positions;

	int i;

	for (i = 0; i < 9; i++)
	{
		getClosingPositions(i, player, positions);
	}

	for (auto &pos : positions)
	{
		if (pos == move)
		{
			score += 2 * multiplier;
			break;
		}
	}
	return score;
}

int Board::next(const std::pair<int, int>& move) const
{
	std::pair<int,int> relativeMove = Position::getRelativePosition(move);

	int nextBoard = 3 * relativeMove.second + relativeMove.first;

	return isFinished(nextBoard) ? -1 : nextBoard;
}

// alex -> in ce board merge dupa "move" tarsnpus in relative position 0..2 0..2
// ATENITIE --> NETESTATA
int Board::goNextBoard(const std::pair<int, int>& move) const 
{

	std::pair <int, int> RelativePosition = Position::getRelativePosition(move);

	if (RelativePosition.first == 0) {
		return 0 + RelativePosition.second;
	}
	else if (RelativePosition.first == 1) {
		return 3 + RelativePosition.second;
	}
	else {
		return 6 + RelativePosition.second;
	}
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
	return 1;
}

bool Board::isValid(const int move) const {

	if (_field[move] == 0)
	{
		int board = Board::getBoard(move);

		if (_macroboard[board] == -1)
		{
			return true;
		}
	}

	return false;
}

bool Board::isValid(const std::pair<int, int> move) const
{
	return isValid( Position::absoluteToAbsolute(move));
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
		if (_macroboard[i] == -1)
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

int Board::getBoard(const std::pair<int, int> & move) const {

	int row = 3 * (move.second / 3);
	int column = move.first / 3;

	return row + column;
}


void Board::applyMove(const std::pair<int, int> & move, const int player)
{
	std::set< std::pair <int, int> > positionsToClose;
	int board = getBoard(move); // board-ul unde pun mutarea
	bool allFlag = false;

	int index = Position::absoluteToAbsolute(move);

	_field[index] = player;
	int id;

	if (finishes(move, player, id)) {
		if (id == player) {
			_macroboard[board] = player;
		}
		if (id == 0) {
			_macroboard[board] = 0;
		}
	}
	else {
		
	}
	updateMacroboard(move);

}
bool Board::isFinished(const int board) const
{
	assert(board != -1);

	std::set < std::pair<int, int> > emptyPositions;

	if (_macroboard[board] == 1 || _macroboard[board] == 2 )
	{
		return true;
	}
	else 
	{
		getEmptyPositions(board, emptyPositions);

		if (emptyPositions.size() == 0)
		{
			return true;
		}
		return false;
	}

}
bool Board::finishes(std::pair<int , int> move , const int player , int &id) const {
	std::set< std::pair<int, int> > positions;
	int board = getBoard(move);
	std::pair<int, int> toRelative = Position::getRelativePosition(move);
	getEmptyPositions(board, positions);
	if (positions.size() == 1) {
		if (Position::getMatrixPosition(this, board, *positions.begin()) == move) {
			id = 0;
			return true;
		}
	}
	positions.clear();
	getClosingPositions(board, player, positions);
	
	for (auto& position : positions) {
		if (toRelative == position) {
			id = player;
			return true;
		}
	}
	id = -1;
	return false;
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

std::ostream & operator<<(std::ostream & os, const Board & b)
{
	os << "macroboard\n";
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			os << b._macroboard[k] << ' ';
			k++;
		}
		os << std::endl;
	}

	os << "\nplayingBoard\n";
	k = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			os << b._field[k] << ' ';
			k++;
			if (j % 3 == 2)
				os << ' ';
		}
		if (i % 3 == 2)
			os << std::endl;
		os << std::endl;
	}
	return os;
}
