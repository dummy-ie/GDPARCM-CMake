#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace gd
{
	class StringUtils
	{
	public:
		static std::vector<std::string> split(const std::string& s, char delimiter);
	};

	inline std::vector<std::string> StringUtils::split(const std::string& s, const char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
}

