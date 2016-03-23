#pragma once


namespace UTTT {
	namespace Core {
		class Utility
		{
		public:
			inline Utility() {};
			inline ~Utility() {};
			static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
			static int stringToInt(const std::string &s);
		};
	}
}
