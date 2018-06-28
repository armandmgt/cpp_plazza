/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#include <thread>
#include <iostream>
#include "Slave.hpp"

plz::Slave::Slave(plz::LinkDescriptor &&descriptor) : master{descriptor}{
	std::cout << "Hello from newly constructed Slave" << std::endl;
}

void plz::Slave::exec() {
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "now exiting" << std::endl;
}
