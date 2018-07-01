/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "enums.hpp"
#include "Master.hpp"

plz::Master::Master(unsigned nbThreads) : _nbThreads{nbThreads} {
}

void plz::Master::run() {
	while (std::cin.good()) {
		auto commands = _parser.getLine();
		//getSlavesWorkLoad -> asks each slave how much work they are currently processing
		runQueueCommand(commands);
		std::this_thread::sleep_for(std::chrono::milliseconds{1});
	}
}

void plz::Master::printData(std::list<plz::Data> data) {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::ofstream logFile;

	std::ostringstream oss;
	oss << std::put_time(&tm, "logfile-%d%m%Y-%H%M.log");
	logFile = std::ofstream(oss.str());
	for (auto const &d : data) {
		std::cout << d.type << ":" << std::endl;
		for (auto const &e : d.data) {
			std::cout << "match: [" << e << "]" << std::endl;
			logFile << e << std::endl;
		}
	}
}

void plz::Master::runQueueCommand(std::deque<plz::Command> commands)
{
	for (auto const &c : commands) {
		std::cout << "Parsed command: [" << c.type << " " << c.filename << "]" << std::endl;
		_slaves.push_back(createSlave(_nbThreads));
		_slaves.back().sendCommand(c);
	}
	for (auto const &s : _slaves) {
//			std::cout << "checking slave" << std::endl;
			if (s.hasData()) {
//				std::cout << "master process has data" << std::endl;
				auto data = s.getData();
//				std::cout << "has " << data.size() << " entries" << std::endl;
				printData(data);
			}
		}
}
