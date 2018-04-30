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

plazza::Shell::Shell() : _input(), _cli(),
        _type({
        {"PHONE_NB", PHONE_NB}, {"EMAIL_ADDR", EMAIL_ADDR},
        {"IP_ADDR", IP_ADDR}
        })
{

}

std::unordered_multimap<plazza::InfoType, std::string> plazza::Shell::getInputMap()
{
	_input.clear();
        CLIParser *c = new CLIParser();
	parseCLIInput(c->getCLI());
        delete c;
	return _input;
}

void plazza::Shell::parseCLIInput(std::vector<std::string> const &_cli)
{
        int     checker = 0;

        for (auto line: _cli) {
                checker = 0;
                for (auto type: _type) {
                        if (std::strstr(line.c_str(), type.first.c_str())) {
                                if (checker > 0) {
                                        _input.clear();
                                       // std::cout << "to many types on one line" << std::endl;
					throw ArgumentError("Too many Information Types on one command");
                                        // to types on one line
                                }
                                storeInputToMap(line, type);
                                checker++;
                        }
                }
                if (checker == 0) {
                	throw ArgumentError("No Information Type given");
                        std::cout << "no type given" << std::endl;
                        //no type given
                }
        }
}

void plazza::Shell::storeInputToMap(std::string const &line, std::pair<const std::string, plazza::InfoType> const &type)
{
        std::string file;
        std::stringstream rd;
        rd.str(line);

        while (std::getline(rd, file, ' ')) {
                if (file != type.first && file != "") {
                	std::cout<<"[" << file << "]" << std::endl;
                        _input.insert(std::pair<InfoType, std::string>(type.second, file));
                }
        }
}