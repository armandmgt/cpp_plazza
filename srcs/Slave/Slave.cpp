/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <poll.h>
#include "Exceptions.hpp"
#include "Slave.hpp"

plazza::Slave::Slave(int threadLimit)
	: _threadLimit(threadLimit), _isChild(false), _pool{}, buffer{},
	_timer(std::chrono::steady_clock::now())
{
}

void plazza::Slave::start()
{
	installSocket();
	if (!_isChild)
		return;
	_pool = std::list<Search>(static_cast<unsigned long>(_threadLimit));
	loop();
}

void plazza::Slave::installSocket()
{
	int sds[2];
	pid_t pid;

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sds) == -1) {
		std::cerr << strerror(errno) << std::endl;
		throw RuntimeError(strerror(errno));
	}
	pid = fork();
	if (pid == 0) {
		close(sds[0]);
		_sd = sds[1];
		_isChild = true;
	} else {
		_sd = sds[0];
		close(sds[1]);
	}
}

void plazza::Slave::loop()
{
	while (true) {
		auto c = readCommand();
		if (timedOut()) {
			std::cout << "timed out !" << std::endl;
			exit(0);
		}
		std::cout << infoTypeToS(c.first) << " "
				<< c.second << std::endl;
	}
}

std::pair<plazza::InfoType, std::string> plazza::Slave::readCommand()
{
	command c = {};

	_sd >> c;
	return std::pair<plazza::InfoType, std::string>(c.type, c.file);
}

void plazza::Slave::feedCommand(plazza::InfoType type, std::string file)
{
	command c = {type};

	sprintf(c.file, "%.128s", file.c_str());
	_sd << c;
}

bool plazza::Slave::timedOut()
{
	std::chrono::seconds elapsed;
	elapsed = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - _timer);
	return elapsed.count() >= 5;
}
