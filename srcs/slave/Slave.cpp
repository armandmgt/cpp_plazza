/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#include <thread>
#include <iostream>
#include <functional>
#include <fstream>
#include "Slave.hpp"

plz::Slave::Slave(plz::LinkDescriptor &&descriptor, unsigned nbThread)
	: _master{std::move(descriptor)},
	  _timer{std::chrono::steady_clock::now()},
	  _thread(nbThread, std::thread([this]() { runThread(); })) {
	std::cout << "Hello from newly constructed Slave" << std::endl;
}

void plz::Slave::exec() {
	Command c{};
	while (!timedOut()) {
		if (_master.hasCommand()) {
			_master.getCommand(c);
			_tasks.push(std::move(c));
			std::cout << "deserialized " << c.type << " " << c.filename << std::endl;
			break;
		}
	}
	exit(0);
}

bool plz::Slave::timedOut()
{
	std::chrono::seconds elapsed;
	elapsed = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - _timer);
	return elapsed.count() >= 5;
}



void plz::Slave::runThread()
{
	while (!done) {
		Command task;
		{
			std::lock_guard<std::mutex> guard(_mTask);
			task = _tasks.front();
			_tasks.pop();
		}
		doParsing(std::move(task));
	}
}

void plz::Slave::doParsing(Command &&cmd)
{
	static regexMap const regexMatch = {
		{InfoType::PHONE_NUMBER, R"((?:(?:\+|00)33|0)\s*[1-9](?:[\s]*\d{2}){4})"},
		{InfoType::EMAIL_ADDRESS, R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"},
		{InfoType::IP_ADDRESS, R"(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
	    		"(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"}
	};

	try {
		auto const &regex = regexMatch.find(cmd.type);
		findData(*regex, std::move(cmd.filename));
	} catch (std::out_of_range &e) {
		throw  std::runtime_error("type requested is unknown");
	}
}

void plz::Slave::findData(const std::pair<const InfoType, std::regex> &regex, std::string &&filename)
{
	std::ifstream file{filename};
	std::string fileLine;
	std::smatch match;

	while (std::getline(file, fileLine)) {
		auto cmdBegin = std::sregex_iterator(fileLine.begin(),
						     fileLine.end(), regex.second);
		auto cmdEnd = std::sregex_iterator();
		for (std::sregex_iterator i = cmdBegin; i != cmdEnd; i++) {
			match = *i;
			_data.emplace({regex.first, match.str()});
			std::cout << match.str() << std::endl;
		}
	}
}
