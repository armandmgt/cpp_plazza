/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, createSlave
*/

#include <sys/socket.h>
#include "LinkDescriptor.hpp"

plz::LinkDescriptor plz::createSlave() {
	int sv[2]{0};

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) == -1)
		return {-1, -1, -1, -1};
	return {};
}
