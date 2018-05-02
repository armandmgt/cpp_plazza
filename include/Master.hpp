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
	#include <unordered_map>
	#include <list>
	#include <fstream>
	#include "plazza.hpp"
	#include "Data.hpp"
	#include "Shell.hpp"

	namespace plazza {

		class Master {
		public:
			explicit Master(int threadLimit);
			~Master() = default;

			void runMaster();

		private:
			void createProcess();
			void outputData(std::list<Data> data);
			void pollShell();
			std::list<int> slaves;
			Shell shell;
			int threadLimit;
			std::ofstream logFile;
		};
	};

#endif
