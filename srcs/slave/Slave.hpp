/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include "network/LinkDescriptor.hpp"

namespace plz {
	template<std::size_t V>
	class Slave {
	public:
		Slave(plz::LinkDescriptor &&descriptor) : _master{std::move(descriptor)}{
			std::cout << "Hello from newly constructed Slave" << std::endl;
		}

		void exec() {
			Command c{};
			while (true) {
				if (_master.hasCommand()) {
					_master.getCommand(c);
					std::cout << "deserialized " << c.type << " " << c.filename << std::endl;
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::cout << "now exiting" << std::endl;
			exit(0);
		}

	private:
		LinkDescriptor _master;
		std::queue<Command> _tasks;
		std::queue<Data> _data;
		std::mutex _mTask;
		std::mutex _mData;
		std::array<std::thread, V> _thread;
	};
}
