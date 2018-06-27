/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Search
*/

#include <iostream>
#include <functional>
#include "Search.hpp"

plazza::Search::Search() : _fileSize(0), _running(false)
{

}

void plazza::Search::parseFile()
{
	if (_data.type == UNKNOWN) {
		throw  std::runtime_error("type requested is unknown");
	} else if (_data.filename.empty()) {
		throw  std::runtime_error("filename is empty");
	}
	_running = true;
	_thread = std::thread(&Search::doParsing, this);
}

void plazza::Search::doParsing()
{
	std::string fileLine;
	std::smatch match;

	while (std::getline(_file, fileLine)) {
		auto cmdBegin = std::sregex_iterator(fileLine.begin(),
						     fileLine.end(), _regex);
		auto cmdEnd = std::sregex_iterator();
		for (std::sregex_iterator i = cmdBegin; i != cmdEnd; i++) {
			match = *i;
			_data.elems.push_back(match.str());
			std::cout << match.str() << std::endl;
		}
	}
	_running = false;
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
		{PHONE_NUMBER, R"((?:(?:\+|00)33|0)\s*[1-9](?:[\s]*\d{2}){4})"},
		{EMAIL_ADDRESS, R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)"},
		{IP_ADDRESS, "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
	    		"(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"}
	};

	try {
		_regex.assign(regexMatch.at(_data.type));
	} catch (std::out_of_range &e) {
		throw  std::runtime_error("type requested is unknown");
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

bool plazza::Search::running() {
	if (!_running && _thread.joinable())
		_thread.join();
	return _running;
}

unsigned short plazza::Search::getStatus()
{
	return static_cast<unsigned short>(_file.tellg() * 100 / _fileSize);
}

std::string plazza::Search::getFileName() const
{
	return _data.filename;
}
