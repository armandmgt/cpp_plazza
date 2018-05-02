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
		auto const &c = readCommand();
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
	std::pair<plazza::InfoType, std::string> command;

	_sd >> command;
	return command;
}

void plazza::Slave::feedCommand(plazza::InfoType type, std::string file)
{
	_sd << std::pair<InfoType, std::string>(type, file);
}

bool plazza::Slave::timedOut()
{
	std::chrono::seconds elapsed;
	elapsed = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - _timer);
	return elapsed.count() >= 5;
}

int plazza::operator>>(int sd, std::pair<plazza::InfoType, std::string> &command)
{
	char buf[512];
	struct pollfd pfd = {sd, POLLIN, 0};

	switch (poll(&pfd, 1, 1000)) {
		case -1:
			throw RuntimeError(strerror(errno));
		case 0:
			break;
		default:
			recv(sd, buf, 512, MSG_DONTWAIT);
			std::string str(strtok(buf, ";"));
			command.first = sToInfoType(str);
			command.second = std::string(strtok(nullptr, ";"));
			break;
	}
	return sd;
}

int plazza::operator<<(int sd,
	       std::pair<plazza::InfoType, std::string> const &command)
{
	std::string s(infoTypeToS(command.first) + ";" + command.second + "\n");

	if (send(sd, s.c_str(), s.size(), 0) == -1)
		throw RuntimeError(strerror(errno));
	return sd;
}
