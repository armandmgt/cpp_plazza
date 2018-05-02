/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Search
*/
#ifndef PLAZZA_SEARCH_HPP
	#define PLAZZA_SEARCH_HPP

	#include <regex>
	#include <list>
	#include <unordered_map>
	#include "plazza.hpp"
	#include "Exceptions.hpp"
	#include "Data.hpp"

	namespace plazza {

		using regexMap = std::unordered_map<InfoType, std::string>;

		class Search {
		public:
			Search(InfoType typeToSearch,
				std::string &fileName);
			Search() = default;
			~Search() = default;

			void setFilename(std::string &filename);
			void setInfoType(InfoType);
			void parseFileData();
			Data getData();
		private:
			void setRegex();

			std::regex _regex;
			Data _data;
		};
	}

#endif
