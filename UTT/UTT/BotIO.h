#pragma once

#include <vector>
#include "Board.h"
namespace UTTT {
	namespace Core {
		class BotIO
		{
		public:
			BotIO();
			inline ~BotIO() {};
			int getBotId()const;
			int getOponentId() const;
			void loop();
		private:
			// static settings
			int _timebank;
			int _timePerMove;
			int _botId;
			Board _playingBoard;
			std::pair<int, std::pair<int, int> > minimax(Board* b, const int player, const int depth);
			std::vector<std::string> _playerNames;
			std::string _myName;
			// dynamic settings
			int _round;
			int _move;

			//Implement this function.
			//type is always "move"
			//return value must be position in x,y presentation
			//(use std::make_pair(x, y))
			std::pair<int, int> action(const std::string &type, int time);

			//Returns random free cell.
			std::pair<int, int> getRandomFreeCell() const;
			void processCommand(const std::vector<std::string> &command);
			void update(const std::string& player, const std::string& type, const std::string& value);
			void setting(const std::string& type, const std::string& value);
			void debug(const std::string &s) const;
		};
	}
}
