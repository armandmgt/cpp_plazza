/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Search
*/

#include <iostream>
#include <functional>
#include "Search.hpp"

plazza::Search::Search(InfoType type, std::string const &fileName)
	: _fileSize(0)
{
	setFilename(fileName);
	setInfoType(type);
}

void plazza::Search::parseFile()
{
	if (_data.type == UNKNOWN) {
		throw  RuntimeError("type requested is unknown");
	} else if (_data.filename.empty()) {
		throw  RuntimeError("filename is empty");
	}
	_thread = std::thread(&Search::doParsing, this);
}

void plazza::Search::doParsing()
{
	std::string fileLine;
	std::smatch match;

	while (getline(_file, fileLine)) {
		auto cmdBegin = std::sregex_iterator(fileLine.begin(),
						     fileLine.end(), _regex);
		auto cmdEnd = std::sregex_iterator();
		for (std::sregex_iterator i = cmdBegin; i != cmdEnd; i++) {
			match = *i;
			_data.elems.push_back(match.str());
		}
	}
}

plazza::Data plazza::Search::getData()
{
	Data rtn(std::move(_data));
	_data.elems.clear();
	return rtn;
}

void plazza::Search::setRegex()
{
	static regexMap const regexMatch = {
		{PHONE_NB, "(0|\\+33|0033)[1-9][0-9]{8}"},
		{EMAIL_ADDR, R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"},
		{IP_ADDR, "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
	    		"(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"}
	};

	try {
		_regex.assign(regexMatch.at(_data.type));
	} catch (std::out_of_range &e) {
		throw  RuntimeError("type requested is unknown");
	}
}

void plazza::Search::setFilename(const std::string &filename)
{
	std::ifstream ifs(filename, std::ifstream::ate | std::ifstream::binary);
	_file = std::ifstream(filename);
	_data.filename = filename;
	_data.elems.clear();
	_fileSize = ifs.tellg();
}

void plazza::Search::setInfoType(plazza::InfoType newType)
{
	_data.type = newType;
	setRegex();
}

bool plazza::Search::running() const {
	return _thread.joinable();
}

unsigned short plazza::Search::getStatus()
{
	return static_cast<unsigned short>(_file.tellg() * 100 / _fileSize);
}
