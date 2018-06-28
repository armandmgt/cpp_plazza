/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#include <iostream>
#include <map>
#include "enums.hpp"
#include "Master.hpp"
#include "network/LinkDescriptor.hpp"

std::ostream &operator <<(std::ostream &os, plz::InfoType type) {
	static std::map<plz::InfoType, std::string> const assoc{
		{plz::InfoType::IP_ADDRESS, "IP_ADDRESS"}, {plz::InfoType::EMAIL_ADDRESS, "EMAIL_ADDRESS"},
		{plz::InfoType::PHONE_NUMBER, "PHONE_NUMBER"}
	};
	return os << assoc.at(type);
}

plz::Master::Master(unsigned nbThreads) : _nbThreads{nbThreads} {
}

void plz::Master::run() {
	while (std::cin.good()) {
		auto commands = _parser.getLine();
		//getSlavesWorkLoad -> asks each slave how much work they are currently processing
		for (auto const &c : commands) {
			std::cout << c.type << " " << c.filename << std::endl;
		}
	}
}
