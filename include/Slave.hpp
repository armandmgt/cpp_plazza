/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#ifndef PLAZZA_SLAVE_HPP
	#define PLAZZA_SLAVE_HPP

	#include <unordered_map>
	#include <list>
	#include "Search.hpp"
	#include "Master.hpp"
	#include "Load.hpp"

	namespace plazza {

		class Slave {
		public:
			Slave(unsigned int &threadLimit);
			~Slave();
			bool feedCommand(InfoType, std::string &file);
			std::list<Load> getLoad();
			std::list<Data> getData();
		private:
			unsigned int _threadLimit;
			std::list<Search> _pool;
			std::unordered_multimap<InfoType, std::string> _buffer;
			std::list<Load>	_load;
		};
	};

#endif //PLAZZA_SLAVE_HPP
