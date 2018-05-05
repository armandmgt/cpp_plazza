/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** globals
*/

#include <string>
#include <unordered_map>
#include "Slave.hpp"
#include "plazza.hpp"

int const SUCCESS = 0;
int const FAILURE = 84;

std::ostream &plazza::operator<<(std::ostream &os, InfoType it)
{
	os << infoTypeToS(it);
	return os;
}

std::ostream &plazza::operator<<(std::ostream &os, CommandType ct)
{
	os << commandTypeToS(ct);
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

plazza::CommandType sToCommandType(std::string const &s)
{
	static std::unordered_map<std::string, plazza::CommandType> const m = {
		{"OPERATION", plazza::OPERATION},
		{"GET_DATA", plazza::GET_DATA},
		{"GET_LOAD", plazza::GET_LOAD},
	};

	if (m.find(s) != m.end()) {
		return m.at(s);
	} else {
		return plazza::NONE;
	}
}

std::string commandTypeToS(plazza::CommandType ct)
{
	static std::unordered_map<plazza::CommandType, std::string> const m = {
		{plazza::NONE, "NONE"},
		{plazza::OPERATION, "OPERATION"},
		{plazza::GET_DATA, "GET_DATA"},
		{plazza::GET_LOAD, "GET_LOAD"},
	};

	return m.at(ct);
}
