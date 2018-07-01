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
			std::cout << "Parsed command: [" << c.type << " " << c.filename << "]" << std::endl;
			_slaves.push_back(createSlave(_nbThreads));
			_slaves.back().sendCommand(c);
		}
		for (auto const &s : _slaves) {
//			std::cout << "checking slave" << std::endl;
			if (s.hasData()) {
				std::cout << "master process has data" << std::endl;
				auto data = s.getData();
				std::cout << "has " << data.size() << " entries" << std::endl;
				printData(data);
			}
		}
		std::this_thread::yield();
	}
}

void plz::Master::printData(std::list<plz::Data> data) {
	for (auto const &d : data) {
		std::cout << d.type << ":" << std::endl;
		for (auto const &e : d.data) {
			std::cout << "match: [" << e << "]" << std::endl;
		}
	}
}
