/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Parser
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Parser.hpp"

std::vector<std::string> splitStringAt(std::istringstream &&input, char delim) {
	std::vector<std::string> commands{};
	std::string command;

	while (std::getline(input, command, delim)) {
		commands.push_back(std::move(command));
	}
	return commands;
}

std::vector<plz::Command> plz::Parser::getLine() {
	std::string input;
	std::vector<plz::Command> commands{};

	while (std::cin.good()) {
		std::getline(std::cin, input);
		auto parts = splitStringAt(std::istringstream{input}, ';');
		for (auto const &c : parts) {
			auto &&next = parseCommand(std::istringstream{c});
			std::move(next.begin(), next.end(), std::back_inserter(commands));
		}
		if (!commands.empty())
			return commands;
	}
	return {};
}

std::vector<plz::Command> plz::Parser::parseCommand(std::istringstream sst) {
	std::vector<Command> cmds{};
	std::string filename;

	while (!sst.eof()) {
		std::getline(sst, filename, ' ');
		cmds.emplace_back("PHONE_NUMBER", std::move(filename));
	}
	auto type = cmds.back().filename;
	std::for_each(cmds.begin(), cmds.end(), [type](auto &c) { c = Command{type, std::move(c.filename)}; });
	cmds.pop_back();
	std::for_each(cmds.begin(), cmds.end(), [type](auto &c) { std::cout << c.type << " " << c.filename << std::endl; });
	return cmds;
}
