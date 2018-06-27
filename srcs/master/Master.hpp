/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#pragma once

#include "parser/Parser.hpp"

namespace plz {
	class Master {
	public:
		explicit Master(unsigned nbThreads);

		void run();

	private:
		unsigned _nbThreads;
		Parser _parser;
	};
}
