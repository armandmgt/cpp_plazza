/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#include <iostream>
#include "enums.hpp"
#include "Master.hpp"

plz::Master::Master(unsigned nbThreads) : _nbThreads{nbThreads} {
}

void plz::Master::run() {
	while (std::cin.good()) {
		auto commands = _parser.getLine();
		//getSlavesWorkLoad -> asks each slave how much work they are currently processing
		for (auto const &c : commands) {
			std::cout << c.type << " " << c.filename << std::endl;
			_slaves.push_back(createSlave());
			_slaves.back().send(c);
		}
	}
}
