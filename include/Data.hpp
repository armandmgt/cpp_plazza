/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Data
*/

#ifndef PLAZZA_DATA_HPP
	#define PLAZZA_DATA_HPP

	#include <string>
	#include <list>
	#include "plazza.hpp"

	namespace plazza {
		class Data {
		public:
			InfoType type = UNKNOWN;
			std::string filename;
			std::list<std::string> elems;
		};
	}

#endif //PLAZZA_DATA_HPP
