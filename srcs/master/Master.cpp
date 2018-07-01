/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#include <iostream>
#include <iomanip>
#include "enums.hpp"
#include "Master.hpp"

plz::Master::Master(unsigned nbThreads) : _nbThreads{nbThreads}
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	_oss << std::put_time(&tm, "logfile-%d%m%Y-%H%M.log");
}

void plz::Master::run() {
	while (std::cin.good()) {
		auto commands = _parser.getLine();
		runQueueCommand(commands);
		std::this_thread::sleep_for(std::chrono::milliseconds{1});
	}
}

void plz::Master::printData(std::list<plz::Data> data) {
	_logFile = std::ofstream(_oss.str());
	for (auto const &d : data) {
		std::cout << d.type << ":" << std::endl;
		for (auto const &e : d.data) {
			std::cout << "match: [" << e << "]" << std::endl;
			_logFile << e << std::endl;
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
		if (s.hasData()) {
			auto data = s.getData();
			printData(data);
		}
	}
}
