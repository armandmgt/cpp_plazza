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
#include "Shell.hpp"
#include "CLIParser.hpp"
#include "Exceptions.hpp"

plazza::Shell::Shell() : _input(), _cli(), _typeChecker(0),
        _type({
        {"PHONE_NB", PHONE_NB}, {"EMAIL_ADDR", EMAIL_ADDR},
        {"IP_ADDR", IP_ADDR}
        })
{
}

std::unordered_multimap<plazza::InfoType, std::string> plazza::Shell::getCommands()
{
	_input.clear();
        CLIParser *c = new CLIParser();
	parseCLIInput(c->getInput());
        delete c;
        if (_input.empty()) {
        	throw ArgumentError("No file given");
        }
	return _input;
}

void plazza::Shell::parseCLIInput(std::vector<std::string> const &_cli)
{
        for (auto line: _cli) {
		_typeChecker = 0;
                for (auto type: _type) {
                	findTypeInCommand(line, type);
                }
                if (_typeChecker == 0) {
                	throw ArgumentError("No Information Type given");
                }
        }
}

void plazza::Shell::findTypeInCommand(std::string const &line, std::pair<const std::string, plazza::InfoType> const &type)
{
	if (std::strstr(line.c_str(), type.first.c_str())) {
		if (_typeChecker > 0) {
			_input.clear();
			throw ArgumentError("Too many Information Types on one command");
		}
		storeInputToMap(line, type);
		_typeChecker++;
	}
}

void plazza::Shell::storeInputToMap(std::string const &line, std::pair<const std::string, plazza::InfoType> const &type)
{
        std::string file;
        std::stringstream rd;
        rd.str(line);

        while (std::getline(rd, file, ' ')) {
                if (file != type.first && file != "") {
                        _input.insert(std::pair<InfoType, std::string>(type.second, file));
                }
        }
}