/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/

#include <thread>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "Master.hpp"

plazza::Master::Master(int threadLimit) : _shell(),
	_threadLimit(static_cast<unsigned int>(threadLimit)),
	_logFile(), _workPriority()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "logfile-%d%m%Y-%H%M.log");
	_logFile = std::ofstream(oss.str());
}

void plazza::Master::createProcess()
{
	_workPriority.push_back({0, new Slave(_threadLimit)});
	_workPriority.back().second->start();
}

void plazza::Master::outputData(std::list<Data> data)
{
	static std::unordered_map<InfoType, std::string> type = {
		{PHONE_NB, "PHONE_NB"}, {EMAIL_ADDR, "EMAL_ADDR"}, {IP_ADDR, "IP_ADDR"}
	};

	for (auto const &e : data) {
		std::cout << "In data loop" << std::endl;
		for (auto const &s : e.elems) {
			//Yammer 2017: No supplimetary data should be shown!
			std::cout << s << std::endl;
			_logFile << s << std::endl;
		}
	}
}

void plazza::Master::retrieveData()
{
	for (auto &slave: _workPriority) {
		std::cout << " In retrieve data\n";
		outputData(slave.second->getData());
	}
}

void plazza::Master::setWorkLoad()
{
	for (auto it = _workPriority.begin(); it != _workPriority.end(); it++) {
		if (!it->second->alive()) {
			delete it->second;
			_workPriority.erase(it++);
		} else {
			it->first = it->second->getLoad().waitingCommands;
		}
	}
}

void plazza::Master::sortSlaveOrder()
{
	_workPriority.sort([](slaveManagement &a, slaveManagement &b) {
		return a.first < b.first;
	});
}

void plazza::Master::distributeIllegalWork(shellInput const &input)
{
	for (auto it : input) {
		std::cout << it.first << " " << it.second << std::endl;
	}
	for (auto const &command : input) {
		setWorkLoad();
		sortSlaveOrder();
		if (_workPriority.empty() ||
		    _workPriority.front().first == (_threadLimit * 2)) {
			createProcess();
		}
		_workPriority.front().second->feedCommand(command.first, command.second);
	}
}

void plazza::Master::runMaster()
{
	std::unordered_multimap<InfoType, std::string> input;

	while (true) {
		try {
			input = _shell.getCommands();
		} catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			return;
		}
		if (input.empty())
			return;
		distributeIllegalWork(input);
		retrieveData();
	}
}
