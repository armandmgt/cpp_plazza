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

plazza::Master::Master(unsigned int threadLimit) : _shell(), _threadLimit(threadLimit),
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
}

void plazza::Master::deleteProcess(slaveManagement const &slave)
{
	//_workPriority.erase(slave);
}

void plazza::Master::outputData(std::list<Data> data)
{
	static std::unordered_map<InfoType, std::string> type = {
		{PHONE_NB, "PHONE_NB"}, {EMAIL_ADDR, "EMAL_ADDR"}, {IP_ADDR, "IP_ADDR"}
	};

	for (auto const &e : data) {
		std::cout << "In data" << std::endl;
		for (auto const &s : e.elems) {
			//Yammer 2017: No supplimetary data should be shown!
			std::cout /*<< type[e.type] << " in " << e.filename << ": "*/ << s << std::endl;
			_logFile /*<< type[e.type] << " in " << e.filename << ": "*/ << s << std::endl;
		}
	}
}

void plazza::Master::retrieveData()
{
	for (auto &slave: _workPriority) {
		outputData(slave.second->getData());
	}
}

void plazza::Master::setWorkLoad()
{
	for (auto slave = _workPriority.begin(); slave != _workPriority.end(); slave++) {//auto &slave: _workPriority) {
		if (!slave->second->alive()) {
			delete[] slave->second;
			slave = _workPriority.erase(slave);

			//deleteProcess(slave);
		} else {
			auto const &workLoad = slave->second->getLoad();
			slave->first = workLoad.waitingCommands;
		}
	}
}

void plazza::Master::sortSlaveOrder()
{
	_workPriority.sort([](slaveManagement &a, slaveManagement &b) {
		return a.first < b.first;
	});
}

void plazza::Master::distributeIllegalWork(std::unordered_multimap<plazza::InfoType, std::string> const &input)
{
	for (auto it : input) {
		std::cout << it.first << " " << it.second << std::endl;
	}
	for (auto const &command : input) {
		setWorkLoad();
		sortSlaveOrder();
		if (_workPriority.empty() || _workPriority.begin()->first == (_threadLimit * 2)) {
			createProcess();
		}
		std::cout << "in FeedCommand" << std::endl;
		_workPriority.begin()->second->feedCommand(command.first, command.second);
	}
}

void plazza::Master::runMaster()
{
	std::unordered_multimap<InfoType, std::string> input;

	while (true) {
		try {
			input = _shell.getCommands();
		} catch (std::exception const &msg) {
			msg.what();
			return;
		}
		distributeIllegalWork(input);
		retrieveData();
	}
}
