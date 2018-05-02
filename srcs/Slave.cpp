/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "Exceptions.hpp"
#include "Slave.hpp"

plazza::Slave::Slave(int threadLimit)
	: _threadLimit(threadLimit), _isChild(false), _pool{}, buffer{}
{
}

void plazza::Slave::start() {
	installSocket();
	if (!_isChild)
		return;
	_pool = std::list<Search>(static_cast<unsigned long>(_threadLimit));
	loop();
}

void plazza::Slave::installSocket() {
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

void plazza::Slave::loop() {

}
