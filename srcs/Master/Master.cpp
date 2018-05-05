/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Master
*/

#include <thread>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <wait.h>
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

void plazza::Master::createProcess(plazza::operation const &ope)
{
	_workPriority.push_back({0, new Slave(_threadLimit)});
	auto const &[waiting, newBorn] = _workPriority.back();
	if (waiting == 0) {
		newBorn->start();
		newBorn->feedCommand(ope);
	}
}
void plazza::Master::outputData(std::list<Data> data)
{
	for (auto const &e : data) {
		std::cout << "in data loop" << std::endl;
		for (auto const &s : e.elems) {
			std::cout << s << std::endl;
			_logFile << s << std::endl;
		}
	}
}

void plazza::Master::retrieveData()
{
	for (auto &[waiting, slave] : _workPriority) {
		if (waiting > 0)
			outputData(slave->getData());
	}
}

void plazza::Master::setWorkLoad()
{
	for (auto &wp : _workPriority) {
		std::cout << "fetching the number of waiting commands" << std::endl;
		wp.first = wp.second->getLoad().waitingCommands;
	}
}

void plazza::Master::sortSlaveOrder()
{
	_workPriority.sort([](slaveManagement &a, slaveManagement &b) {
		return a.first < b.first;
	});
}

bool plazza::Master::trySlaves(plazza::operation const &ope)
{
	for (auto it = _workPriority.begin(); it != _workPriority.end();) {
		auto &[waiting, slave] = *it;
		if (waiting < _threadLimit * 2) {
			if (!slave->feedCommand(ope)) {
				delete it->second;
				_workPriority.erase(it++);
			} else {
				return true;
			}
		}
	}
	return false;
}

void plazza::Master::distributeIllegalWork(shellInput const &input)
{
	for (auto const &ope : input) {
		setWorkLoad();
		sortSlaveOrder();
		if (_workPriority.empty() || !trySlaves(ope)) {
			createProcess(ope);
		}
	}
}

void plazza::Master::runMaster()
{
	shellInput input;

	while (true) {
		if (std::cin.eof()) {
			int status = 0;
			wait(&status);
			return;
		}
		input = _shell.getCommands();
		if (input.empty())
			continue;
		distributeIllegalWork(input);
		retrieveData();
	}
}

std::list<plazza::Load> plazza::Master::getLoad() const
{
	std::list<plazza::Load> returnList;

	for (auto it : _workPriority)
		returnList.push_back(it.second->getLoad());
	return returnList;
}
