#include "stdafx.h"
#include "BotIO.h"
#include "Utility.h"
#include "Board.h"
#include "Position.h"
#include <ctime>
#include <time.h>
#include <random>
#include <queue>
using namespace UTTT::Core;

//Bot initialization.
BotIO::BotIO() {
	srand(static_cast<unsigned int>(time(0)));
}


int UTTT::Core::BotIO::getBotId() const
{
	return _botId;
}

int UTTT::Core::BotIO::getOponentId() const
{
	if (getBotId() == 1)
	{
		return 2;
	}
	return 1;
}



void BotIO::loop() {
	std::string line;
	std::vector<std::string> command;
	command.reserve(256);

	while (std::getline(std::cin, line)) {
		processCommand(Utility::split(line, ' ', command));
	}
}

std::pair<int, std::pair<int, int>> UTTT::Core::BotIO::minimax(Board b, const int player, int alpha, int beta, const int depth)
{
	if (depth == 0)
	{
		return std::make_pair(b.eval(player), std::make_pair(-1, -1));
	}
	std::set<std::pair<int, int> > emptyPositions;
	b.getEmptyPositions(emptyPositions);
	Board previousBoard = Board(b);
	std::pair<int, std::pair<int, int> > current;
	std::pair<int, int> toMove;
	for (auto pos : emptyPositions)
	{
		if (b.isValid(pos))
		{
			b.applyMove(pos, player);
			current = minimax(b, UTTT::Core::Utility::getNextPlayer(player), -beta, -alpha, depth - 1);
			current.first *= -1;
			if (current.first >= beta)
			{
				return std::make_pair(beta, pos);
			}
			if (current.first  > alpha)
			{
				alpha = current.first;
				toMove = pos;
			}
			b = Board(previousBoard);
		}
	}
	return std::make_pair(alpha, toMove);
}
	
std::pair<int, int> BotIO::action(const std::string &type, int time) {
	return minimax(&_playingBoard, getBotId(), 2).second;
	
	
	std::vector<int> playingBoards;
	std::set<std::pair<int, int> > positions;
	std::vector<std::pair<int, int> > pos;
	std::vector < std::pair<int, int> > blankPositions;
	_playingBoard.getCurrentPlayingBoards(playingBoards);
	std::priority_queue<std::pair<int, std::pair<int, int> > >que;
	for (auto b : playingBoards)
	{
		if (_playingBoard.getClosingPositions(b, getBotId(), positions))//if i can close
		{
			que.push(std::make_pair(100, Utility::closeGame(&_playingBoard, b, getOponentId(), positions)));
		}
		if (_playingBoard.getClosingPositions(b, getOponentId(), positions))//if opponent can close
		{
			que.push(std::make_pair(95, Utility::blockGame(&_playingBoard, b, getOponentId(), positions)));//block
		}

		if (_playingBoard.throwOpponentInBlankGame(b, getOponentId(), blankPositions))
		{
			que.push(std::make_pair(90, *blankPositions.begin()));
		}
		if (_playingBoard.throwOpponentNoAdvantage(b, getOponentId(), pos))
		{
			que.push(std::make_pair(85, *pos.begin()));
		}
	}
	if (que.size())
	{
		return que.top().second;
		}
	return getRandomFreeCell();
	}

bool UTTT::Core::BotIO::goMinimax() const
{
	if (_move <= 13)
	{
		return false;
	}
	if (_move <= 20)
	{
		int random = rand() % 100;
		if (random < 50)
		{
			return false;
		}
	}
	return true;
}

std::pair<int, int> BotIO::action(const std::string &type, int time) {
	
	if (goMinimax())
	{
		return minimax(_playingBoard, getBotId(), -INF, INF, 5).second;
	}
	return heuristic();
}

std::pair<int, int> BotIO::getRandomFreeCell() const {
	debug("Using random algorithm.");
	std::vector<int> freeCells;
	for (int i = 0; i < 81; ++i) {
		int blockId = ((i / 27) * 3) + (i % 9) / 3;
		if (_playingBoard._macroboard[blockId] == -1 && _playingBoard._field[i] == 0) {
			freeCells.push_back(i);
		}
	}
	int randomCell = freeCells[rand() % freeCells.size()];
	return std::make_pair(randomCell % 9, randomCell / 9);
}

void BotIO::processCommand(const std::vector<std::string> &command) {
	if (command[0] == "action") {
		auto point = action(command[1], Utility::stringToInt(command[2]));
		std::cout << "place_move " << point.first << " " << point.second << std::endl << std::flush;
	}
	else if (command[0] == "update") {
		update(command[1], command[2], command[3]);
	}
	else if (command[0] == "settings") {
		setting(command[1], command[2]);
	}
	else {
		debug("Unknown command <" + command[0] + ">.");
	}
}

void BotIO::update(const std::string& player, const std::string& type, const std::string& value) {
	if (player != "game" && player != _myName) {
		// It's not my update!
		return;
	}

	if (type == "round") {
		_round = Utility::stringToInt(value);
	}
	else if (type == "move") {
		_move = Utility::stringToInt(value);
	}
	else if (type == "macroboard" || type == "field") {
		std::vector<std::string> rawValues;
		Utility::split(value, ',', rawValues);
		std::vector<int>::iterator choice = (type == "field" ? _playingBoard._field.begin() : _playingBoard._macroboard.begin());
		std::transform(rawValues.begin(), rawValues.end(), choice, Utility::stringToInt);
	}
	else {
		debug("Unknown update <" + type + ">.");
	}
}

void BotIO::setting(const std::string& type, const std::string& value) {
	if (type == "timebank") {
		_timebank = Utility::stringToInt(value);
	}
	else if (type == "time_per_move") {
		_timePerMove = Utility::stringToInt(value);
	}
	else if (type == "player_names") {
		Utility::split(value, ',', _playerNames);
	}
	else if (type == "your_bot") {
		_myName = value;
	}
	else if (type == "your_botid") {
		_botId = Utility::stringToInt(value);
	}
	else {
		debug("Unknown setting <" + type + ">.");
	}
}

void BotIO::debug(const std::string &s) const {
	std::cerr << s << std::endl << std::flush;
}

