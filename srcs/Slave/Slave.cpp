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
		throw std::runtime_error(strerror(errno));
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
		auto cmd = readCommand();
		if (timedOut()) {
			std::cout << "timed out !" << std::endl;
			exit(0);
		}
		if (cmd.ope.type == UNKNOWN)
			continue;
		std::cout << "received command " << infoTypeToS(cmd.ope.type)
			  << " " << cmd.ope.file << std::endl;
		_timer = std::chrono::steady_clock::now();
	}
}

plazza::command plazza::Slave::readCommand()
{
	command c = {};

	_sd >> c;
	return c;
}

bool plazza::Slave::feedCommand(operation const &ope)
{
	command c = {OPERATION, ope};

	try {
		_sd << c;
	} catch (std::runtime_error const &e) {
		std::cerr << "feedCommand failed !" << std::endl;
		return false;
	}
	std::cerr << "feedCommand succeeded" << std::endl;
	return true;
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
