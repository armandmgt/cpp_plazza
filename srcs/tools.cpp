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
		{"PHONE_NUMBER", plazza::PHONE_NUMBER},
		{"EMAIL_ADDRESS", plazza::EMAIL_ADDRESS},
		{"IP_ADDRESS", plazza::IP_ADDRESS},
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
		{plazza::PHONE_NUMBER, "PHONE_NUMBER"},
		{plazza::EMAIL_ADDRESS, "EMAIL_ADDRESS"},
		{plazza::IP_ADDRESS, "IP_ADDRESS"},
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
