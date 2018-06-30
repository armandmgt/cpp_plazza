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

static std::mutex printMutex;

plz::Slave::Slave(plz::LinkDescriptor &&descriptor, unsigned nbThread)
	: _master{std::move(descriptor)},
	  _timer{std::chrono::steady_clock::now()},
	  _threads(nbThread) {
	std::cout << "Hello from newly constructed Slave" << std::endl;
	std::generate(_threads.begin(), _threads.end(), [this]() {
		return std::thread{[this]() { runThread(); }};
	});
}

plz::Slave::~Slave() {
	_cv.notify_all();
	for (auto &th : _threads)
		th.join();
	std::cout << "All threads are exited" << std::endl;
}

void plz::Slave::exec() {
	Command c{};
	while (!timedOut()) {
		if (_master.hasCommand()) {
			_master.getCommand(c);
			{
				std::lock_guard<std::mutex> guard{printMutex};
				std::cout << "deserialized " << c.type << " " << c.filename << std::endl;
			}
			{
				std::lock_guard<std::mutex> lock{_mTask};
				_tasks.push(std::move(c));
			}
			_cv.notify_one();
		}
	}
	{ // Use this to print safely (no mix of outputs) in a thread
		std::lock_guard<std::mutex> lock{printMutex};
		std::cout << "Timed out ! Now exiting" << std::endl;
	}
}

bool plz::Slave::timedOut()
{
	std::chrono::seconds elapsed;
	elapsed = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - _timer);
	if (_running > 0) {
		_timer = std::chrono::steady_clock::now();
		return false;
	}
	return elapsed.count() >= 5;
}

void plz::Slave::runThread()
{
	while (true) {
		Command task;
		{
			std::unique_lock<std::mutex> lock{_mTask};
			_cv.wait(lock);
			if (_tasks.empty())
				return;
			task = std::move(_tasks.front());
			_tasks.pop();
			_running++;
		}
		{
			std::lock_guard<std::mutex> guard{printMutex};
			std::cout << "I received a command and I am now parsing !" << std::endl;
		}
		try {
			doParsing(std::move(task));
			_running--;
		} catch (std::regex_error &e) {
			{
				std::lock_guard<std::mutex> guard{printMutex};
				std::cerr << "Regex error: " << e.what() << std::endl;
			}
		}
	}
}

void plz::Slave::doParsing(Command &&cmd)
{
	static regexUMap const regexMatch{
		{InfoType::PHONE_NUMBER, R"((?:(?:\+|00)33|0)\s*[1-9](?:[\s]*\d{2}){4})"},
		{InfoType::EMAIL_ADDRESS, R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"},
		{InfoType::IP_ADDRESS, R"(\d\d?\d?\.\d\d?\d?\.\d\d?\d?\.\d\d?\d?)"}
	};

	try {
		findData(regexMatch.at(cmd.type), std::move(cmd));
	} catch (std::out_of_range &e) {
		{
			std::lock_guard<std::mutex> guard{printMutex};
			std::cerr << "Type requested is unknown" << std::endl;
		}
	} catch (std::exception &e) {
		{
			std::lock_guard<std::mutex> guard{printMutex};
			std::cerr << "Search error: " << e.what() << std::endl;
		}
	}
}

void plz::Slave::findData(const std::string &reg, Command &&command)
{
	std::ifstream file{command.filename};
	std::regex regex(reg);
	std::string fileLine;
	std::smatch match;


	if (!file)
		throw std::runtime_error{"Invalid file"};
	while (std::getline(file, fileLine)) {
		std::sregex_iterator cmdBegin{fileLine.begin(), fileLine.end(), regex};
		std::sregex_iterator cmdEnd{};
		for (std::sregex_iterator i = cmdBegin; i != cmdEnd; i++) {
			match = *i;
			_data.emplace(command.type, match.str());
			std::cout << match.str() << std::endl;
		}
	}
}
