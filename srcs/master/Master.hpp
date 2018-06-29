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

	private:
		unsigned const _nbThreads;
		Parser _parser;
		std::deque<LinkDescriptor> _slaves{};
	};
}
