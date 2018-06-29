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
#include "network/LinkDescriptor.hpp"

namespace plz {
	class Slave {
		using regexMap = std::unordered_map<InfoType, std::regex>;
	public:
		explicit Slave(plz::LinkDescriptor &&descriptor, unsigned nbThread);

		bool timedOut();
		void runThread();
		void doParsing(Command &&cmd);
		void exec();
		void findData(const std::pair<const InfoType, std::regex> & regex, std::string &&filename);

	private:
		std::atomic<bool> done{false};
		LinkDescriptor _master;
		std::queue<Command> _tasks{};
		std::queue<std::pair<InfoType, std::string>> _data{};
		std::mutex _mTask{};
		std::mutex _mData{};
		std::chrono::steady_clock::time_point _timer;
		std::vector<std::thread> _thread;
	};
}
