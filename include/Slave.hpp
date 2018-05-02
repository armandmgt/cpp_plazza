/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#ifndef PLAZZA_SLAVE_HPP
	#define PLAZZA_SLAVE_HPP

	#include <list>
	#include "plazza.hpp"
	#include "Search.hpp"
	#include "Data.hpp"
	#include "Load.hpp"

	namespace plazza {
		class Slave {
		public:
			explicit Slave(int threadLimit);
			~Slave() = default;

			void start();
			void feedCommand(InfoType type, std::string file);
			Load getLoad();
			std::list<Data> getData();
		private:
			int _threadLimit;
			int _sd;
			bool _isChild;
			std::list <Search> _pool;
			std::unordered_multimap<InfoType, std::string> buffer;

			void installSocket();

			void loop();
		};
	}

#endif //PLAZZA_SLAVE_HPP
