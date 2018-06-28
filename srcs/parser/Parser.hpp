/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Parser
*/

#pragma once

#include <vector>
#include "serializable/Command.hpp"

namespace plz {
	class Parser {
	public:
		Parser() = default;

		~Parser() = default;

		std::vector<Command> getLine();

		std::vector<Command> parseCommand(std::istringstream sst);
	};
}
