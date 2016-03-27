#pragma once
#include <set>
namespace UTTT {
	namespace Core {
		class Utility
		{
		public:
			inline Utility() {};
			inline ~Utility() {};
			static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
			static int stringToInt(const std::string &s);
			static std::pair<int, int> closeGame(const std::vector<int> macroboard, const int board, const int myself, const std::set<std::pair<int, int> >& possibleClosingPositions);
			static std::pair<int, int> blockGame(const std::vector<int> macroboard, const int board, const int opponent, const std::set<std::pair<int, int> >& possibleClosingPositions);
		};
	}
}
