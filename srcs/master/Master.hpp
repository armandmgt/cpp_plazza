/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#pragma once

#include <deque>
#include "parser/Parser.hpp"
#include "network/LinkDescriptor.hpp"

namespace plz {
	class Master {
	public:
		explicit Master(unsigned nbThreads);

		void run();
		void runQueueCommand(std::deque<Command> cmds);

	private:
		unsigned _nbThreads;
		Parser _parser;
		std::deque<LinkDescriptor> _slaves{};

		void printData(std::list<Data> data);
	};
}
