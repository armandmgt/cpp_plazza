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
#include "Shell.hpp"
#include "Exceptions.hpp"

plazza::Shell::Shell() : _input(), _typeChecker(0),
        _type({
        {"PHONE_NB", PHONE_NB}, {"EMAIL_ADDR", EMAIL_ADDR},
        {"IP_ADDR", IP_ADDR}
        })
{
}

std::unordered_multimap<plazza::InfoType, std::string> plazza::Shell::getCommands()
{
	while (!_input.empty()) {
		_input.erase(_input.begin());
	}
	_input.clear();
	parseCLIInput(_cli.getInput());
        if (_input.empty()) {
        	throw ArgumentError("No file given");
        }
	return _input;
}

void plazza::Shell::parseCLIInput(std::vector<std::string> const &input)
{
        for (auto const &command: input) {
		_typeChecker = 0;
                for (auto const &type: _type) {
                	findTypeInCommand(command, type);
                }
                if (_typeChecker == 0) {
                	throw ArgumentError("No Information Type given");
                }
        }
}

void plazza::Shell::findTypeInCommand(std::string const &command, std::pair<const std::string, plazza::InfoType> const &type)
{
	auto res = std::find_first_of(command.begin(), command.end(), type.first.begin(), type.first.end());
	if (auto i = command.find(type.first)) {//std::strstr(command.c_str(), type.first.c_str())) {
		std::cout << i << std::endl;
		if (_typeChecker > 0) {
			_input.clear();
			throw ArgumentError("Too many Information Types on one command");
		}
		storeInputToMap(command, type);
		_typeChecker++;
	}
}

void plazza::Shell::storeInputToMap(std::string const &command, std::pair<const std::string, plazza::InfoType> const &type)
{
        std::string file;
        std::stringstream rd;
        rd.str(command);

        while (std::getline(rd, file, ' ')) {
                if (file != type.first && !file.empty()) {
                        _input.insert(std::pair<InfoType, std::string>(type.second, file));
                }
        }
}