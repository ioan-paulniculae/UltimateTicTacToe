#include "stdafx.h"
#include "Utility.h"
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

