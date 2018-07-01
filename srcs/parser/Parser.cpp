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

plz::Parser::Parser() : _th{[this]() { runThread(); }} {
}

plz::Parser::~Parser() {
	_th.join();
}

void plz::Parser::runThread() {
	std::string input;

	while (std::cin.good()) {
		if (!std::getline(std::cin, input))
			continue;
		auto parts = splitStringAt(std::istringstream{input}, ';');
		for (auto const &c : parts) {
			auto &&next = parseCommand(c);
			std::lock_guard<std::mutex> lock{_m};
			std::move(next.begin(), next.end(), std::back_inserter(_deque));
		}
	}
}

std::deque<plz::Command> plz::Parser::getLine() {
	std::lock_guard<std::mutex> lock{_m};
	return std::move(_deque);
}

std::vector<plz::Command> plz::Parser::parseCommand(const std::string &input) {
	std::vector<Command> cmds{};

	auto parts = splitStringAt(std::istringstream{input}, ' ');
	auto type = parts.back();
	try {
		std::for_each(parts.begin(), parts.end() - 1, [&type, &cmds](std::string &p) {
			cmds.emplace_back(type, std::move(p));
		});
	} catch (std::out_of_range const &e) {
		std::cerr << "Invalid command" << std::endl;
	}
	return cmds;
}
