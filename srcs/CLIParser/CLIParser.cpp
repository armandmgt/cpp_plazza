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
#include "Exceptions.hpp"
#include "CLIParser.hpp"

plazza::CLIParser::CLIParser()
{
}

plazza::CLIParser::~CLIParser()
{

}

std::vector<std::string> plazza::CLIParser::getCLI()
{
        std::string line;

	std::getline(std::cin, line);
	std::stringstream rd;
	rd.str(line);
	while (std::getline(rd, line, ';')) {
		_cli.push_back(line);
	}
	if (_cli.empty()) {
		throw ArgumentError("No input given");
        }
        return _cli;
}