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
		auto cmdBegin = std::sregex_iterator(fileLine.begin(),
						     fileLine.end(), _regex);
		auto cmdEnd = std::sregex_iterator();

		for (std::sregex_iterator i = cmdBegin; i != cmdEnd; i++) {
			match = *i;
			_foundData.push_back(match.str());
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
		{plazza::EMAIL_ADDR, "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"},
		{plazza::IP_ADDR,
			"(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"}
	};

	_regex.assign(regexMatch.at(_typeToSearch));
}
/*
int main()
{
	std::string fileName("hiden_data");
	plazza::Search addr(plazza::EMAIL_ADDR, fileName);

	addr.parseFileData();
	std::cout << "Find email address : " << std::endl;
	auto list = addr.getFileData();
	for (std::string node : list) {
		std::cout << "Find data : " << node << std::endl;
	}

	plazza::Search phone(plazza::PHONE_NB, fileName);
	phone.parseFileData();
	auto list1 = phone.getFileData();
	std::cout << "Find phone number : " << std::endl;
	for (std::string node : list1) {
		std::cout << "Find data : " << node << std::endl;
	}

	plazza::Search ip(plazza::IP_ADDR, fileName);
	ip.parseFileData();
	auto list2 = ip.getFileData();
	std::cout << "Find ip address: " << std::endl;
	for (std::string node : list2) {
		std::cout << "Find data : " << node << std::endl;
	}
}*/