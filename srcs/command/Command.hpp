/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Command
*/

#pragma once

#include <string>
#include "enums.hpp"

namespace plz {
	struct Command {
		InfoType type{};
		std::string filename;
	};

	struct CommandWrapper {
		explicit operator bool() const { return valid; }

		bool valid = true;
		Command cmd{};
	};
}
