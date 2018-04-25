/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Search
*/

#include <iostream>
#include <fstream>
#include "Search.hpp"

plazza::Search::Search(plazza::InfoType typeToSearch,
		       std::string &fileName) :
	_typeToSearch(typeToSearch), _fileName(fileName)
{
	setRegex();
}

void plazza::Search::parseFileData()
{
	std::ifstream file(_fileName);
	std::string fileLine;
	std::smatch match;

	while (getline(file, fileLine)) {
		std::cout << "nb Match : " << std::regex_match(fileLine, match, _regex) << std::endl;
		std::cout << "Size of match object : " << match.size() << std::endl;
		for (size_t i = 0; i < match.size(); i++) {
			std::cout << "Result value : " <<  match[i].str() << std::endl;
		}
	}
}

std::list<std::string> plazza::Search::getFileData()
{
	return _foundData;
}

void plazza::Search::setRegex()
{
	static regexMap const regexMatch = {
		{plazza::PHONE_NB, "(0|\\+33|0033)[1-9][0-9]{8}"},
		{plazza::EMAIL_ADDR, "[a-zA-Z0-9_.-]+ ‘@’ [a-zA-Z0-9_.-]+"},
		{plazza::IP_ADDR,
			"((25[0-5]|"
   			"2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|[^0-9])){4}"}
	};

	_regex.assign(regexMatch.at(_typeToSearch));
}

int main()
{
	std::string fileName("hiden_ip_address");
	plazza::Search item(plazza::IP_ADDR, fileName);

	item.parseFileData();
	auto list = item.getFileData();

	for (std::string node : list) {
		std::cout << "Find data : " << node << std::endl;
	}
}