/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, createSlave
*/

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "LinkDescriptor.hpp"
#include "slave/Slave.hpp"

plz::LinkDescriptor plz::createSlave() {
	int sv[8]{0};

	for (auto i = 0; i < 4; i++) {
		 if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv + 2 * i) == -1)
			return {};
	}
	auto pid = fork();
	if (pid == -1)
		return {};
	for (auto i = 0; i < 4; i++) {
		if (pid == 0) {
			std::cout << "in child, closing " << sv[2 * i] << " and saving " << sv[2 * i + 1] << std::endl;
			close(sv[2 * i]);
			sv[i] = sv[2 * i + 1];
		} else {
			std::cout << "in father, closing " << sv[2 * i + 1] << " and saving " << sv[2 * i] << std::endl;
			close(sv[2 * i + 1]);
			sv[i] = sv[2 * i];
		}
	}
	if (pid == 0)
		Slave(LinkDescriptor{sv[0], sv[1], sv[2], sv[3]}).exec();
	return {sv[0], sv[1], sv[2], sv[3]};
}
