/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Command
*/

#pragma once

#include <string>
#include <map>
#include "enums.hpp"

namespace plz {
	struct Command {
		Command() = default;
		Command(const std::string &t, std::string &&f) : filename{f} {
			static std::map<std::string, InfoType> const assoc{
				{"IP_ADDRESS", InfoType::IP_ADDRESS}, {"EMAIL_ADDRESS", InfoType::EMAIL_ADDRESS},
				{"PHONE_NUMBER", InfoType::PHONE_NUMBER}
			};
			type = assoc.at(t);
		}

		InfoType type{};
		std::string filename;
	};
}