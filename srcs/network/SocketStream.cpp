/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, SocketStream
*/

#include <unistd.h>
#include "SocketStream.hpp"

plz::SocketStream::SocketStream(int socket) : socket{socket} {
}

plz::SocketStream::~SocketStream() {
	close(socket);
}

bool plz::SocketStream::hasData() const {
	return false;
}

bool plz::SocketStream::operator<<(const plz::ISerializable &obj[[maybe_unused]]) const {
	return false;
}
