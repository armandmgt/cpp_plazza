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
#include "SocketStream.hpp"

plz::SocketStream::SocketStream(int socket) : _socket{socket} {
}

plz::SocketStream::~SocketStream() {
	close(_socket);
}

bool plz::SocketStream::hasData() const {
	pollfd fds{_socket, POLLIN, 0};
	nfds_t nfds= 1;

	if (poll(&fds, nfds, 0) == -1)
		_socket = -1;
	return static_cast<bool>(fds.revents & POLLIN);
}

bool plz::SocketStream::operator<<(const plz::ISerializable &obj[[maybe_unused]]) const {
	if (_socket == -1)
		return false;
	auto &&s = obj.serialize();
	std::cout << "writing [" << s << "] to socket " << _socket << std::endl;
	s += '\n';
	write(_socket, s.c_str(), s.size());
	fflush(stdout);
	return true;
}

plz::SocketStream::operator bool() const {
	return _socket != -1;
}

std::string plz::SocketStream::getLine() const {
	static char cbuf[4097]{0};
	size_t rsize = 4096;

	if (cbuf[0] != 0)
		rsize -= strlen(cbuf);
	std::cout << "socket before: " << _socket << std::endl;
	if (read(_socket, cbuf + strlen(cbuf), rsize) <= 0)
		_socket = -1;
	std::cout << "received [" << cbuf << "] socket after: " << _socket << std::endl;
	std::istringstream sst{cbuf};
	std::string line;
	while (std::getline(sst, line))
		_buffer.push(std::move(line));
	if (cbuf[strlen(cbuf) - 1] != '\n') {
		strcpy(cbuf, _buffer.back().c_str());
		_buffer.pop();
	}
	if (_buffer.empty())
		return {};
	auto ret = _buffer.front();
	_buffer.pop();
	return ret;
}
