/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Search
*/
#ifndef PLAZZA_SEARCH_HPP
	#define PLAZZA_SEARCH_HPP

	#include <regex>
	#include <unordered_map>
	#include <list>
	#include "plazza.hpp"

	namespace plazza {

		using regexMap = std::unordered_map<plazza::InfoType, std::string>;

		class Search {
		public:
			Search(plazza::InfoType typeToSearch,
				std::string &fileName);
			~Search() = default;

			void parseFileData();
			std::list<std::string> getFileData();
		private:
			void setRegex();

			plazza::InfoType _typeToSearch;
			std::regex _regex;
			std::string &_fileName;
			std::list<std::string> _foundData;
		};
	}

#endif
