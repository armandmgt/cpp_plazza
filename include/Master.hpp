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

	#include "plazza.hpp"

	namespace plazza {

		class Master {
		public:
			Master();
			~Master();

			void outputFileDataResult();
			void createProcesses();

		private:
			std::list<std::string> _outputResult;
			std::unordered_map<InfoType, std::string> _shellInput;
		};
	};

#endif
