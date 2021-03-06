/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#pragma once

#include <mutex>
#include <thread>
#include <atomic>
#include <regex>
#include <unordered_map>
#include <condition_variable>
#include "network/LinkDescriptor.hpp"

namespace plz {
	class Slave {
		using regexUMap = std::unordered_map<InfoType, std::string>;
	public:
		explicit Slave(plz::LinkDescriptor &&descriptor, unsigned nbThread);
		~Slave();

		bool timedOut();
		void runThread();
		void doParsing(Command &&cmd);
		void exec();
		void findData(const std::string &regex, Command &&command);

	private:
		std::condition_variable _cv{};
		LinkDescriptor _master;
		std::queue<Command> _tasks{};
		std::mutex _mTask{};
		std::mutex _mData{};
		std::chrono::steady_clock::time_point _timer;
		std::vector<std::thread> _threads;
		std::atomic_int _running{0};
	};
}
