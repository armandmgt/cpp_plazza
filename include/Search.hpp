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
	#include <thread>
	#include <fstream>
	#include "plazza.hpp"
	#include "Exceptions.hpp"
	#include "Data.hpp"

	namespace plazza {

		using regexMap = std::unordered_map<InfoType, std::string>;

		class Search {
		public:
			Search(InfoType type,
			       std::string const &fileName);
			Search() = default;
			~Search() = default;

			void setFilename(const std::string &filename);
			void setInfoType(InfoType);
			void parseFile();
			bool running() const;
			Data getData();
			unsigned short getStatus();
			std::string getFileName() const;

		private:
			std::ifstream::pos_type _fileSize;
			std::thread _thread;
			std::regex _regex;
			std::ifstream _file;
			Data _data;

			void doParsing();
			void setRegex();
		};
	}

#endif
