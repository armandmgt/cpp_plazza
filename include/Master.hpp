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
			using shellInput = std::list<operation>;
			using slaveManagement =
				std::pair<unsigned long, Slave *>;
		public:
			explicit Master(int threadLimit);
			~Master() = default;

			void runMaster();
			void distributeIllegalWork(shellInput const &input);

		private:
			void outputData(std::list<Data> data);
			void retrieveData();
			void setWorkLoad();
			void sortSlaveOrder();
			void createProcess(const operation &ope);
			bool trySlaves(const operation &ope);

			Shell _shell;
			unsigned int _threadLimit;
			std::ofstream _logFile;
			std::list<slaveManagement> _workPriority;
		};
	};

#endif
