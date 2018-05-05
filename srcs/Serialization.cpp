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

	template<typename T>
	void serializeValue(std::ostringstream &oss,
			    T const &value)
	{
		oss << R"(")" << value << R"(")";
	}

	template<typename T>
	void serializeProp(std::ostringstream &oss,
			   std::string const &propName,
			   T const &value)
	{
		oss << R"(")" << propName << R"(":)";
		serializeValue(oss, value);
	}

	std::pair<std::string, std::string>
	deserializeProp(std::istringstream &iss) {
		std::pair<std::string, std::string> p;

		std::getline(iss.ignore(), p.first, '"');
		std::getline(iss.ignore(2), p.second, '"');
		return p;
	}

	std::istringstream receiveData(int sd)
	{
		size_t msglen = 0;
		struct pollfd pfd = {sd, POLLIN, 0};

		switch (poll(&pfd, 1, 1000)) {
			case -1:
				throw std::runtime_error(strerror(errno));
			case 0:
				return std::istringstream();
			default:
				recv(sd, &msglen, sizeof(msglen), MSG_DONTWAIT);
				std::unique_ptr<char[]> buf(new char[msglen]());
				recv(sd, buf.get(), msglen - 1, MSG_DONTWAIT);
				return std::istringstream(buf.get());
		}
	}

	int sendData(std::ostringstream const &oss, int sd)
	{
		size_t msglen = oss.str().size();
		if (send(sd, &msglen, sizeof(msglen), MSG_NOSIGNAL) == -1 ||
		    send(sd, oss.str().c_str(), msglen, MSG_NOSIGNAL) == -1)
			throw std::runtime_error("");
		return sd;
	}
}

int plazza::operator>>(int sd, plazza::command &command)
{
	std::istringstream iss = receiveData(sd);

	if (!iss.good() || iss.eof() || iss.str().empty())
		return sd;
	std::cerr << "serializing: [" << iss.str() << "]" << std::endl;
	iss.ignore();
	command.cmd = sToCommandType(deserializeProp(iss).second);
	iss.ignore();
	command.ope.type = sToInfoType(deserializeProp(iss).second);
	iss.ignore();
	command.ope.file = deserializeProp(iss).second;
	return sd;
}

int plazza::operator<<(int sd, plazza::command &command)
{
	std::ostringstream oss;

	oss << startJsonObj;
	serializeProp(oss, "cmd", command.cmd);
	oss << sepJson;
	serializeProp(oss, "type", command.ope.type);
	oss << sepJson;
	serializeProp(oss, "filename", command.ope.file);
	oss << endJsonObj;
	std::cerr << "serializing: [" << oss.str() << "]" << std::endl;
	return sendData(oss, sd);
}
