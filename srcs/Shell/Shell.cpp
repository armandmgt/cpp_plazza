/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** shell
*/

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>
#include "Shell.hpp"
#include "Exceptions.hpp"

plazza::Shell::Shell() : _cli()
{
}

std::list<plazza::operation> plazza::Shell::getCommands()
{
	std::list<operation> commands{};

	auto cliInput = _cli.getInput();
	for (auto const &line : cliInput) {
		auto file = line.substr(0, line.find(' ', 0));
		auto type = line.substr(line.find(' ', 0) + 1);
		if (sToInfoType(type) == UNKNOWN)
			throw ArgumentError("unknown information type");
		commands.push_back({sToInfoType(type), file});
	}
	return commands;
}

