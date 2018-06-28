/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Data
*/

#pragma once

#include <string>
#include <list>
#include "enums.hpp"

namespace plz {
	struct Data {
		Data() = default;

		InfoType type{};
		std::list<std::string> data{};
	};
}
