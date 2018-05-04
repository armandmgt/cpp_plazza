/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Load
*/

#ifndef PLAZZA_LOAD_HPP
	#define PLAZZA_LOAD_HPP

	#include <unordered_map>

	namespace plazza {
		struct Load {
			Load() : waitingCommands(0), threadLoads({}) {};
			unsigned long waitingCommands;
			std::unordered_map<std::string, unsigned short int> threadLoads;
		};
	}

#endif //PLAZZA_LOAD_HPP
