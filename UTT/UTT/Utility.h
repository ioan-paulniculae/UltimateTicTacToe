#pragma once
#include <set>
#include "Board.h"
namespace UTTT {
	namespace Core {
		class Utility
		{
		public:
			inline Utility() {};
			inline ~Utility() {};
			static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
			static int stringToInt(const std::string &s);
			static std::pair<int, int> closeGame(const Board* b, const int board, const int opponent, const std::set<std::pair<int, int> >& possibleClosingPositions);
			static std::pair<int, int> blockGame(const Board* b, const int board, const int opponent, const std::set<std::pair<int, int> >& possibleClosingPositions);
			static int getNextPlayer(const int currentPlayer);
		};
	}
}
