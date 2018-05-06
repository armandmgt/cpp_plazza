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

namespace {
	int fdBlock(int fd, bool block) {
		int flags;
		if(flags = fcntl(fd, F_GETFL, 0); flags == -1) {
			return -1;
		}
		block ? flags &= ~O_NONBLOCK : flags |= O_NONBLOCK;
		return fcntl(fd, F_SETFL, flags);
	}
}

void plazza::Slave::installSocket()
{
	int sds[4] = {0};
	pid_t pid;

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sds) == -1 ||
		socketpair(PF_LOCAL, SOCK_STREAM, 0, sds + 2) == -1) {
		std::cerr << strerror(errno) << std::endl;
		throw std::runtime_error(strerror(errno));
	}
	pid = fork();
	if (pid == 0) {
		close(sds[0]);
		close(sds[2]);
		_sd = sds[1];
		_sdData = sds[3];
		fdBlock(_sd, false);
		fdBlock(_sdData, true);
		_isChild = true;
	} else {
		_sd = sds[0];
		_sdData = sds[2];
		close(sds[1]);
		close(sds[3]);
		fdBlock(_sd, false);
		fdBlock(_sdData, true);
	}
}

void plazza::Slave::loop()
{
	while (true) {
		auto cmd = readCommand();
		if (timedOut())
			exit(0);
		switch (cmd.cmd) {
			case GET_DATA: checkForData(); break;
			case OPERATION: launchOperation(cmd); break;
			default: break;
		}
		if (cmd.cmd == OPERATION)
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
		return false;
	}
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
	command c = {GET_DATA};
	std::list<Data> d;
	Data buf{};

	_sd << c;
	_sdData >> buf;
	while (buf.type != END) {
		d.push_back(buf);
		_sdData >> buf;
	}
	return d;
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

void plazza::Slave::checkForData() {
	for (auto &t : _pool) {
		if (!t.running()) {
			auto d = t.getData();
			_sdData << d;
		}
	}
	Data d{END};
	_sdData << d;
}

void plazza::Slave::retrieveLoad() {
}

void plazza::Slave::launchOperation(const command &cmd) {
	for (auto &t : _pool) {
		if (!t.running()) {
			t.setInfoType(cmd.ope.type);
			t.setFilename(cmd.ope.file);
			try {
				t.parseFile();
				break;
			} catch (std::runtime_error const &e) {
				std::cerr << "thread: "
					  << e.what() << std::endl;
			}
		}
	}
}
