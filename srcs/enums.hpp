/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, enums
*/

#pragma once

#include <map>

namespace plz {
	enum class InfoType {
		PHONE_NUMBER,
		EMAIL_ADDRESS,
		IP_ADDRESS,
		MAX_INFO_TYPE
	};

	inline std::ostream &operator <<(std::ostream &os, plz::InfoType type) {
		static std::map<plz::InfoType, std::string> const assoc{
			{plz::InfoType::IP_ADDRESS, "IP_ADDRESS"}, {plz::InfoType::EMAIL_ADDRESS, "EMAIL_ADDRESS"},
			{plz::InfoType::PHONE_NUMBER, "PHONE_NUMBER"}
		};
		return os << assoc.at(type);
	}
}
