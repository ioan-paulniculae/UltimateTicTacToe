#include "stdafx.h"
#include "Position.h"
#include "Board.h"
#include "Utility.h"
#include <queue>
#include <vector>

using namespace UTTT::Core;

std::vector<std::string>& Utility::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	elems.clear();
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int UTTT::Core::Utility::stringToInt(const std::string & s)
{
	std::istringstream ss(s);
	int result;
	ss >> result;
	return result;
}

int UTTT::Core::Utility::getNextPlayer(const int currentPlayer)
{
	return currentPlayer == 1 ? 2 : 1;
}
std::pair<int, int> UTTT::Core::Utility::closeGame(const Board* b, const int board, const int opponent, const std::set<std::pair<int, int>>& possibleClosingPositions)
{
	//(priority, pair)
	std::priority_queue<std::pair<int,std::pair<int, int> > > que;
	std::set<std::pair<int, int> > dummySet;
	int nextPlayingBoard;
	for (auto& closingPosition : possibleClosingPositions)
	{
		nextPlayingBoard = b->next(closingPosition);
		if (nextPlayingBoard == -1 ||
			nextPlayingBoard == board)
		{
			que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
			continue;
		}
		if (b->isClosed(nextPlayingBoard))
		{
			que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
			continue;
		}
		if (b->isEmpty(nextPlayingBoard))
		{
			que.push(make_pair(std::numeric_limits<int>::max(), closingPosition));
			continue;
		}

		if (!b->getClosingPositions(nextPlayingBoard, opponent, dummySet))
		{
			que.push(make_pair(std::numeric_limits<int>::max() / 2, closingPosition));
			continue;
		}

		que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
		dummySet.clear();
		
		
	}
	return Position::getMatrixPosition(b, board, que.top().second);
}

std::pair<int, int> UTTT::Core::Utility::blockGame(const Board* b, const int board, const int opponent, const std::set<std::pair<int, int> >& possibleClosingPositions)
{
	std::priority_queue<std::pair<int, std::pair<int, int> > > que;
	std::set<std::pair<int, int> > dummySet;
	int nextPlayingBoard;
	for (auto& closingPosition : possibleClosingPositions)
	{
		nextPlayingBoard = b->next(closingPosition);
		//if i place and allow him to place wherever he pleases
		if (nextPlayingBoard == -1 ||
			//or I send him in the same game (where he can win) and he has more than 1 winning possibility
			(nextPlayingBoard == board && possibleClosingPositions.size() > 1))
		{
			que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
			continue;
		}
		if (b->isClosed(nextPlayingBoard))
		{
			que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
			continue;
		}
		if (b->isEmpty(nextPlayingBoard))
		{
			que.push(make_pair(std::numeric_limits<int>::max(), closingPosition));
			continue;
		}

		if (!b->getClosingPositions(nextPlayingBoard, opponent, dummySet))
		{
			que.push(make_pair(std::numeric_limits<int>::max() / 2, closingPosition));
			continue;
		}

		que.push(make_pair(std::numeric_limits<int>::min(), closingPosition));
		dummySet.clear();
	}
	return Position::getMatrixPosition(b, board, que.top().second);
}
