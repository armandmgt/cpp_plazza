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
		public:
			Load();
			~Load();
			unsigned int _waitingCommands;
			list<unsigned short int> _threadLoads;
		};
	}

#endif //PLAZZA_LOAD_HPP
