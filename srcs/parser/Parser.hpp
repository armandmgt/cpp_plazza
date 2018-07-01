/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Parser
*/

#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include <deque>
#include "serializable/Command.hpp"

namespace plz {
	class Parser {
	public:
		Parser();
		~Parser() = default;

		std::deque<Command> getLine();

		std::vector<Command> parseCommand(const std::string &input);

	private:
		std::mutex _m{};
		std::thread _th;
		std::deque<Command> _deque{};

		void runThread();
	};
}
