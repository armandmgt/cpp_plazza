/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#ifndef PLAZZA_SLAVE_HPP
	#define PLAZZA_SLAVE_HPP

	#include <vector>
	#include "plazza.hpp"
	#include "Search.hpp"
	#include "Data.hpp"
	#include "Load.hpp"
	#include "Serialization.hpp"

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
			std::vector<Search> _pool;
			std::unordered_multimap<InfoType, std::string> _buffer;
			std::chrono::steady_clock::time_point _timer;

			void installSocket();
			void loop();
			std::pair<InfoType, std::string> readCommand();
			bool timedOut();
			bool alive() const;
		};
	}


#endif //PLAZZA_SLAVE_HPP
