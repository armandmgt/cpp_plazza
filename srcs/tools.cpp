/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** globals
*/

#include <string>
#include <unordered_map>
#include "plazza.hpp"

int const SUCCESS = 0;
int const FAILURE = 84;

std::ostream &plazza::operator<<(std::ostream &os, InfoType it)
{
	os << infoTypeToS(it);
	return os;
}

plazza::InfoType sToInfoType(std::string const &s)
{
	static std::unordered_map<std::string, plazza::InfoType> const m = {
		{"PHONE_NB", plazza::PHONE_NB},
		{"EMAIL_ADDR", plazza::EMAIL_ADDR},
		{"IP_ADDR", plazza::IP_ADDR},
	};

	if (m.find(s) != m.end()) {
		return m.at(s);
	} else {
		return plazza::UNKNOWN;
	}
}

std::string infoTypeToS(plazza::InfoType it)
{
	static std::unordered_map<plazza::InfoType, std::string> const m = {
		{plazza::PHONE_NB, "PHONE_NB"},
		{plazza::EMAIL_ADDR, "EMAIL_ADDR"},
		{plazza::IP_ADDR, "IP_ADDR"},
		{plazza::UNKNOWN, "UNKNOWN"},
	};

	return m.at(it);
}
