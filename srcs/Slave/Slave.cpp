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
#include <fcntl.h>
#include <cstdlib>
#include "Exceptions.hpp"
#include "Slave.hpp"

plazza::Slave::Slave(int threadLimit)
	: _threadLimit(threadLimit), _isChild(false), _pool{}, _buffer{},
	_timer(std::chrono::steady_clock::now())
{
}

plazza::Slave::~Slave() {
	close(_sd);
}

void plazza::Slave::start()
{
	installSocket();
	if (!_isChild)
		return;
	_pool = std::vector<Search>(static_cast<unsigned long>(_threadLimit));
	loop();
}

void plazza::Slave::installSocket()
{
	int sds[2] = {0};
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
		std::cout << "sd in child: " << _sd << std::endl;
	} else {
		_sd = sds[0];
		close(sds[1]);
		std::cout << "sd in parent: " << _sd << std::endl;
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
		if (c.first == UNKNOWN)
			continue;
		std::cout << "received command " << infoTypeToS(c.first)
			  << " " << c.second << std::endl;
	}
}

std::pair<plazza::InfoType, std::string> plazza::Slave::readCommand()
{
	command c = {};

	_sd >> c;
	return {c.type, c.file};
}

void plazza::Slave::feedCommand(plazza::InfoType type, const std::string &file)
{
	command c = {type, 0};

	sprintf(c.file, "%.128s", file.c_str());
	std::cout << "in feed command in slave\n";
	_sd << c;
}

bool plazza::Slave::timedOut()
{
	std::chrono::seconds elapsed;
	elapsed = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::steady_clock::now() - _timer);
	return elapsed.count() >= 5;
}

std::list<plazza::Data> plazza::Slave::getData() {
	std::list<plazza::Data> list;
	for (auto &t : _pool)
		list.push_back(t.getData());
	return list;
}

plazza::Load plazza::Slave::getLoad() {
	plazza::Load load;
	size_t running = 0;

	for (auto &t : _pool) {
		running += t.running() ? 1 : 0;
		load.threadLoads.emplace(t.getFileName(), t.getStatus());
	}
	load.waitingCommands = _buffer.size() + running;
	return load;
}

bool plazza::Slave::alive() const {
	int error = 0;
	socklen_t len = sizeof(error);

	int rtn = getsockopt(_sd, SOL_SOCKET, SO_ERROR, &error, &len);
	return !(rtn != 0 || error != 0);
}
