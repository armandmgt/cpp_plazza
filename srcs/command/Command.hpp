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
	class Command {
	public:
		Command() = default;
		Command(InfoType type, std::string &&filename);

		explicit operator bool() const;

	private:
		bool _invalid{true};

	public:
		InfoType type{};
		std::string filename;
	};
}
