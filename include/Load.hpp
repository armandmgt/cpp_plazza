/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Load
*/

#ifndef PLAZZA_LOAD_HPP
	#define PLAZZA_LOAD_HPP

	#include <list>

	namespace plazza {
		class Load {
			unsigned int waitingCommands;
			std::list<unsigned short int> threadLoads;
		};
	}

#endif //PLAZZA_LOAD_HPP
