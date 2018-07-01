/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, SocketStream
*/

#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <poll.h>
#include <sys/wait.h>
#include "SocketStream.hpp"

plz::SocketStream::SocketStream(int socket) : _socket{socket} {
}

plz::SocketStream::SocketStream(plz::SocketStream &&rhs) noexcept {
	std::swap(_socket, rhs._socket);
	std::swap(_buffer, rhs._buffer);
}

plz::SocketStream &plz::SocketStream::operator=(plz::SocketStream &&rhs) noexcept {
	std::swap(_socket, rhs._socket);
	std::swap(_buffer, rhs._buffer);
	return *this;
}

plz::SocketStream::~SocketStream() {
	close(_socket);
}

bool plz::SocketStream::hasData() const {
	pollfd fds{_socket, POLLIN, 0};
	nfds_t nfds = 1;

	if (poll(&fds, nfds, 0) == -1 || fds.revents & POLLHUP ||
		fds.revents & POLLNVAL || fds.revents & POLLERR)
		_socket = -1;
	return static_cast<bool>(fds.revents & POLLIN);
}

bool plz::SocketStream::operator<<(const plz::ISerializable &obj) const {
	if (_socket == -1)
		return false;
	auto &&s = obj.serialize();
	s += '\n';
	write(_socket, s.c_str(), s.size());
	return true;
}

plz::SocketStream::operator bool() const {
	return _socket != -1;
}

bool plz::SocketStream::getLine(std::string &string) const {
	static char cbuf[4097]{0};
	ssize_t rsize = 4096;

	if (cbuf[0] != 0)
		rsize -= strlen(cbuf);
	if (read(_socket, cbuf + strlen(cbuf), static_cast<size_t>(rsize)) <= 0) {
		std::cout << "socket " << _socket << " closed" << std::endl;
		wait(nullptr);
		_socket = -1;
		return false;
	}
	std::istringstream sst{cbuf};
	std::string line;
	while (std::getline(sst, line))
		_buffer.push(std::move(line));
	if (cbuf[strlen(cbuf) - 1] != '\n') {
		strcpy(cbuf, _buffer.back().c_str());
		_buffer.back() = "";
	}
	if (_buffer.empty())
		return false;
	string = _buffer.front();
	_buffer.pop();
	return true;
}
