/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#include <thread>
#include <iostream>
#include "Slave.hpp"

plz::Slave::Slave(plz::LinkDescriptor &&descriptor) : master{std::move(descriptor)}{
	std::cout << "Hello from newly constructed Slave" << std::endl;
}

void plz::Slave::exec() {
	Command c{};
	while (true) {
		if (master.hasCommand()) {
			master.getCommand(c);
			std::cout << "deserialized " << c.type << " " << c.filename << std::endl;
			break;
		}
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "now exiting" << std::endl;
	exit(0);
}
