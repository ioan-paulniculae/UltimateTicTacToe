#include "stdafx.h"
#include "BotIO.h"
#include "Utility.h"
#include "Board.h"
#include "Position.h"
#include <ctime>
#include <time.h>
#include <random>

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

std::pair<int, std::pair<int, int>> UTTT::Core::BotIO::minimax(Board* b, const int player, const int depth)
{
	if (depth == 0)
	{
		return std::make_pair(b->eval(player), std::make_pair(-1, -1));
	}
	std::set<std::pair<int, int> > emptyPositions;
	b->getEmptyPositions(emptyPositions);
	Board previousBoard = Board(*b);
	int globalScore = -std::numeric_limits<int>::max();
	int current;
	std::pair<int, int> toMove;
	for (auto pos : emptyPositions)
	{
		if (b->isValid(pos))
		{
			b->applyMove(pos, player);
			current = minimax(b, UTTT::Core::Utility::getNextPlayer(player), depth - 1).first;
			if (current > globalScore)
			{
				toMove = pos;
				globalScore = current;
			}
		}
	}

	return std::make_pair(globalScore, toMove);
}
	
std::pair<int, int> BotIO::action(const std::string &type, int time) {
	return minimax(&_playingBoard, getBotId(), 2).second;
	
	
	std::vector<int> playingBoards;
	std::set<std::pair<int, int> > positions;
	std::vector<std::pair<int, int> > pos;
	std::vector < std::pair<int, int> > blankPositions;
	_playingBoard.getCurrentPlayingBoards(playingBoards);
	int ver;
	_playingBoard.getEmptyPositions(positions);
	for (auto &x : positions) {
		ver = _playingBoard.getBoard(x);
		std::cerr << _playingBoard;

	}
	positions.clear();
	for (auto b : playingBoards)
	{
		if (_playingBoard.getClosingPositions(b, getBotId(), positions))//if i can close
		{
			return Utility::closeGame(&_playingBoard, b, getOponentId(), positions);
		}
		if (_playingBoard.getClosingPositions(b, getOponentId(), positions))//if opponent can close
		{
			return Utility::blockGame(&_playingBoard, b, getOponentId(), positions);//block the fucker
		}
		//to do: ALL
		//minimax 
		if (_playingBoard.throwOpponentInBlankGame(b, getOponentId(), blankPositions))
		{
			return *blankPositions.begin();
		}
		if (_playingBoard.throwOpponentNoAdvantage(b, getOponentId(), pos))
		{
			return *pos.begin();
		}
	}

	//TESTE
	//bool test = _playingBoard.isValid(32);
	//std::set<std::pair<int,int> > vector;
	//Board::getEmptyPositions(vector);
	//bool test = _playingBoard.isFinished(3);
	//bool test1 =_playingBoard.isFinished(2);
	//bool test2 = _playingBoard.isFinished(4);
	//bool test3 = _playingBoard.isFinished(5);
	
	return getRandomFreeCell();

	
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

