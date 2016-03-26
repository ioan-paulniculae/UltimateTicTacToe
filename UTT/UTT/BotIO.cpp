#include "stdafx.h"
#include "BotIO.h"
#include "Utility.h"
#include "Board.h"
#include "Position.h"
using namespace UTTT::Core;

//Bot initialization.
BotIO::BotIO() {
	srand(static_cast<unsigned int>(time(0)));
	_field.resize(81);
	_macroboard.resize(9);
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
	
std::pair<int, int> BotIO::action(const std::string &type, int time) {

	Board board(_field, _macroboard);
	std::vector<int> playingBoards;
	std::set<std::pair<int, int> > positions;
	board.getCurrentPlayingBoards(playingBoards);

	for (auto b : playingBoards)
	{
		if (board.getClosingPositions(b, getBotId(), positions))//if i can close
		{
			for (auto& position : positions)
			{
				//TO DO Paul
				//get best closing position
			}
		}
		if (board.getClosingPositions(b, getOponentId(), positions))//if opponent can close
		{
			//To Do Paul
			//block best opponents game
		}
		//to do: ALL
		//minimax 

		//to do: Calin
		//if there exists:
		//generate all positions that send the opponent to blank game
		//and return true,
		//else, return false


		//to do: Alexandru + Theo
		//select from the empty spaces the positions
		//that send the oponent to a game where he cannot close(0 or 1 on same row/column/diagonal)
		//chose the best one from them:


	}

	return getRandomFreeCell();
}

std::pair<int, int> BotIO::getRandomFreeCell() const {
	debug("Using random algorithm.");
	std::vector<int> freeCells;
	for (int i = 0; i < 81; ++i) {
		int blockId = ((i / 27) * 3) + (i % 9) / 3;
		if (_macroboard[blockId] == -1 && _field[i] == 0) {
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
		std::vector<int>::iterator choice = (type == "field" ? _field.begin() : _macroboard.begin());
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

