/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, createSlave
*/

#include <unistd.h>
#include <sys/socket.h>
#include "LinkDescriptor.hpp"
#include "Slave.hpp"

plz::LinkDescriptor plz::createSlave() {
	int sv[8]{0};

	for (auto i = 0; i < 4; i++) {
		 if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv + 2 * i) == -1)
			return {};
	}
	auto pid = fork();
	for (auto i = 0; i < 4; i++) {
		if (pid == 0) {
			close(sv[2 * i]);
			sv[i] = sv[2 * i];
		} else {
			close(sv[2 * i + 1]);
			sv[i] = sv[2 * i + 1];
		}
	}
	if (pid == 0)
		Slave(LinkDescriptor{sv[0], sv[1], sv[2], sv[3]}).exec();
	return {sv[0], sv[1], sv[2], sv[3]};
}
