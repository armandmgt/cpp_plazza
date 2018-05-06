/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CLIPaser
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Exceptions.hpp"
#include "CLIParser.hpp"

plazza::CLIParser::CLIParser() : _cli()
{
}

plazza::CLIParser::~CLIParser()
{
	_cli.clear();
}

std::vector<std::string> plazza::CLIParser::getInput()
{
        std::string line;

	_cli.clear();
	std::getline(std::cin, line);
	std::stringstream rd;
	rd.str(line);
	while (std::getline(rd, line, ';')) {
		_cli.push_back(line);
	}
        return _cli;
}