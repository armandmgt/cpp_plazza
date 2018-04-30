/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CLIPaser
*/

#include <iostream>
#include <vector>
#include "CLIParser.hpp"

plazza::CLIParser::CLIParser()
{
        _cli = NULL;
}

plazza::CLIParser::~CLIParser() = default;
{

}

std::vector plazza::CLIParser::getCLI()
{
        std::string line;

        while (std::getline(std::cin, line, ';')) {
                _cli.push_back(line);
        }
        if (_cli.empty()) {
                //error
        }
        return _cli;

}