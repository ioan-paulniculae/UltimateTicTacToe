#include "stdafx.h"
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

std::pair<int, int> UTTT::Core::Utility::closeGame(const std::vector<int> macroboard, const int board, const int myself, const std::set<std::pair<int, int>>& possibleClosingPositions)
{
	std::priority_queue<std::pair<int, int> > que;
	int nextPlayingBoard;
	for (auto& closingPosition : possibleClosingPositions)
	{
		nextPlayingBoard = Position::nextBoard(macroboard, closingPosition);
		
	}

}

std::pair<int, int> UTTT::Core::Utility::blockGame(const std::vector<int> macroboard, const int board, const int opponent, const std::set<std::pair<int, int>>& possibleClosingPositions)
{
	return std::pair<int, int>();
}
