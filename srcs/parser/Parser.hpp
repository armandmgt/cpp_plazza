/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Parser
*/

#pragma once

#include "command/Command.hpp"

namespace plz {
	class Parser {
	public:
		Parser() = default;

		~Parser() = default;

		CommandWrapper getLine();
	};
}
