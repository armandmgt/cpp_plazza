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
#include "ISerializable.hpp"

namespace plz {
	struct Command : public ISerializable {
		Command() = default;
		Command(Command &&) = default;
		Command(const std::string &t, std::string &&f) : filename{f} {
			static std::map<std::string, InfoType> const assoc{
				{"IP_ADDRESS", InfoType::IP_ADDRESS}, {"EMAIL_ADDRESS", InfoType::EMAIL_ADDRESS},
				{"PHONE_NUMBER", InfoType::PHONE_NUMBER}
			};
			type = assoc.at(t);
		}

		Command &operator =(Command &&) = default;

		std::string serialize() const final;
		void deserialize(std::string &&data) final;

		InfoType type{};
		std::string filename;
	};
}
