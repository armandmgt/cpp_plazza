/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Master
*/

#ifndef PLAZZA_MASTER_HPP
	#define PLAZZA_MASTER_HPP

	#include <string>
	#include <list>
	#include <utility>
	#include <fstream>
	#include "Shell.hpp"
	#include "Slave.hpp"

	namespace plazza {

		class Master {
			using slaveManagement = std::pair<unsigned long, Slave *>;
			//using slaveManagement = std::list<std::pair<unsigned long, Slave>>;
		public:
			explicit Master(int threadLimit);
			~Master() = default;

			void runMaster();

		private:
			void createProcess();
			void outputData(std::list<Data> data);
			void distributeIllegalWork(std::unordered_multimap<InfoType, std::string> const &input);
			void retrieveData();
			void setWorkLoad();
			void sortSlaveOrder();

			Shell _shell;
			unsigned int _threadLimit;
			std::ofstream _logFile;
			std::list<slaveManagement> _workPriority;
		};
	};

#endif
