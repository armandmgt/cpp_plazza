/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Serialization
*/

#include <string>
#include <sys/socket.h>
#include <poll.h>
#include <cstring>
#include <cerrno>
#include <sstream>
#include <iostream>
#include "Serialization.hpp"
#include "Exceptions.hpp"
#include "Slave.hpp"

namespace {
	auto startJsonObj = '{';
	auto endJsonObj = '}';

	auto startJsonArr = '[';
	auto endJsonArr = ']';

	auto sepJson = ',';

	void serializeValue(std::ostringstream &oss,
			    std::string const &value)
	{
		oss << R"(")" << value << R"(")";
	}

	void serializeValue(std::ostringstream &oss,
			    int const &value)
	{
		oss << value;
	}

	template<typename U>
	void serializeValue(std::ostringstream &oss,
			    std::list<U> const &value)
	{
		oss << startJsonArr;
		for (const auto &it : value) {
			serializeValue(oss, it);
			oss << sepJson;
		}
		oss << endJsonArr;
	}

	template<typename T>
	void serializeProp(std::ostringstream &oss,
			   std::string const &propName,
			   T const &value)
	{
		oss << R"(")" << propName << R"(":)";
		serializeValue(oss, value);
	}

	template<typename T>
	std::pair<std::string, T>
	deserializeProp(std::istringstream &iss) {
		std::pair<std::string, std::string> p;

		std::getline(iss.ignore(), p.first, '"');
		std::getline(iss.ignore(2), p.second, '"');
		return p;
	}

	template<>
	std::pair<std::string, int>
	deserializeProp(std::istringstream &iss) {
		std::pair<std::string, int> pair;
		std::string number;

		std::getline(iss.ignore(), pair.first, '"');
		iss.ignore(2);
		iss >> pair.second;
		return pair;
	}

	template<>
	std::pair<std::string, std::list<std::string>>
	deserializeProp(std::istringstream &iss) {
		std::pair<std::string, std::list<std::string>> pair{};
		std::string value;

		std::getline(iss.ignore(), pair.first, '"');
		iss.ignore(3);
		while (iss.peek() != endJsonArr) {
			iss >> value;
			iss.ignore(2);
			pair.second.emplace_back(value);
		}
		return pair;
	}

	template<>
	std::pair<std::string, std::list<int>>
	deserializeProp(std::istringstream &iss) {
		std::pair<std::string, std::list<int>> pair{};
		int value;

		std::getline(iss.ignore(), pair.first, '"');
		iss.ignore(3);
		while (iss.peek() != endJsonArr) {
			iss >> value;
			iss.ignore(2);
			pair.second.push_back(value);
		}
		return pair;
	}

	std::istringstream receiveData(int sd)
	{
		size_t msglen = 0;
		struct pollfd pfd = {sd, POLLIN, 0};

		switch (poll(&pfd, 1, 1000)) {
			case -1:
				throw std::runtime_error("This is not working ??");
			case 0:
				return std::istringstream();
			default:
				recv(sd, &msglen, sizeof(msglen), MSG_DONTWAIT);
				std::unique_ptr<char[]> buf(new char[msglen]());
				recv(sd, buf.get(), msglen, MSG_DONTWAIT);
				return std::istringstream(buf.get());
		}
	}

	int sendData(std::ostringstream const &oss, int sd)
	{
		size_t msglen = oss.str().size() + 1;
		if (send(sd, &msglen, sizeof(msglen), MSG_NOSIGNAL) == -1) {
			std::cout << "this is the first send() of sendData" << std::endl;
			throw std::runtime_error(std::string("first: ") + strerror(errno));
		} else if (send(sd, oss.str().c_str(), msglen, MSG_NOSIGNAL) == -1) {
			std::cout << "this is the second send() of sendData" << std::endl;
			throw std::runtime_error(std::string("second: ") + strerror(errno));
		}
		return sd;
	}
}

int plazza::operator>>(int sd, plazza::command &command)
{
	std::istringstream iss = receiveData(sd);

	if (!iss.good() || iss.eof() || iss.str().empty())
		return sd;
	iss.ignore();
	command.cmd = sToCommandType(deserializeProp<std::string>(iss).second);
	iss.ignore();
	command.ope.type = sToInfoType(deserializeProp<std::string>(iss).second);
	iss.ignore();
	command.ope.file = deserializeProp<std::string>(iss).second;
	std::cerr << command.cmd << std::endl;
	std::cerr << command.ope.type<< std::endl;
	std::cerr << command.cmd << std::endl;
	return sd;
}

int plazza::operator<<(int sd, plazza::command &command)
{
	std::ostringstream oss;

	oss << startJsonObj;
	serializeProp(oss, "cmd", commandTypeToS(command.cmd));
	oss << sepJson;
	serializeProp(oss, "type", infoTypeToS(command.ope.type));
	oss << sepJson;
	serializeProp(oss, "filename", command.ope.file);
	oss << endJsonObj;
	return sendData(oss, sd);
}

int plazza::operator>>(int sd, plazza::Data &cmd)
{
	std::istringstream iss = receiveData(sd);

	if (!iss.good() || iss.eof() || iss.str().empty())
		return sd;
	iss.ignore();
	cmd.type = sToInfoType(deserializeProp<std::string>(iss).second);
	iss.ignore();
	cmd.filename = deserializeProp<std::string>(iss).second;
	iss.ignore();
	cmd.elems = deserializeProp<std::list<std::string>>(iss).second;
	return sd;
}

int plazza::operator<<(int sd, plazza::Data &cmd)
{
	std::ostringstream oss;

	oss << startJsonObj;
	serializeProp(oss, "type", infoTypeToS(cmd.type));
	oss << sepJson;
	serializeProp(oss, "filename", cmd.filename);
	oss << sepJson;
	serializeProp<std::list<std::string>>(oss, "elems", cmd.elems);
	oss << endJsonObj;
	return sendData(oss, sd);
}

int plazza::operator>>(int sd, plazza::Load &cmd)
{
	std::istringstream iss = receiveData(sd);
	std::list<std::string> filenames;
	std::list<int> progression;
	std::unordered_map<std::string, unsigned short int> rebuildMap{};


	if (!iss.good() || iss.eof() || iss.str().empty())
		return sd;
	iss.ignore();
	cmd.waitingCommands = static_cast<unsigned long>(deserializeProp<int>(iss).second);
	iss.ignore();
	filenames = deserializeProp<std::list<std::string>>(iss).second;
	iss.ignore();
	progression = deserializeProp<std::list<int>>(iss).second;
	for (size_t i = 0; i < filenames.size(); i++) {
		rebuildMap[filenames.back()] = static_cast<unsigned short>(progression.back());
		filenames.pop_back();
		progression.pop_back();
	}
	cmd.threadLoads = rebuildMap;
	return sd;
}

int plazza::operator<<(int sd, plazza::Load &cmd)
{
	std::ostringstream oss;
	std::list<std::string> filenames;
	std::list<unsigned short int> progression;

	for (const auto &it : cmd.threadLoads) {
		filenames.push_back(it.first);
		progression.push_back(it.second);
	}
	oss << startJsonObj;
	serializeProp(oss, "waitingCommands", cmd.waitingCommands);
	oss << sepJson;
	serializeProp(oss, "filenames", filenames);
	oss << sepJson;
	serializeProp(oss, "progression", progression);
	oss << endJsonObj;
	return sendData(oss, sd);
}