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
#include "../CLIParser/CLIParser.hpp"

plazza::Shell::Shell() : _input(), _cli(),
        _type({
        {"PHONE_NB", PHONE_NB}, {"EMAIL_ADDR", EMAIL_ADDR},
        {"IP_ADDR", IP_ADDR}
        })
{

}

plazza::Shell::~Shell() = default
{

}

unordered_map<plazza::InfoType, std::string> plazza::Shell::getInputMap()
{
        CLIParser *c;
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
                                storeInputToMap(line, type;
                                if (checker > 0) {
                                        _input.clear();
	                                std::cout << "no type found in the CLI" << std::endl;
                                        // to types on one line
                                }
                                checker++;
                        }
                }
                if (checker == 0) {
                        std::cout << "no type given" << std::endl;
                        //no type given
                }
        }
}

void plazza::Shell::storeInputToMap(std::string &line,
                std::map<std::string, plazza::Infotype> &type)
{
        std::string file;
        std::stringstream rd;
        rd.str(line);
        while (std::getline(rd, file, ' ')) {
                if (file != type.first) {
                        _input.push_back(type.second, file);
                }
        }
}