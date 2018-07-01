/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, LinkDescriptor
*/

#include "LinkDescriptor.hpp"

plz::LinkDescriptor::LinkDescriptor(int sCommand, int sData, int sRequest, int sInfo)
	: _commands{sCommand}, _data{sData}, _requests{sRequest}, _infos{sInfo} {
}

bool plz::LinkDescriptor::isAlive() {
	return false;
}

bool plz::LinkDescriptor::hasData() const {
	return _data.hasData();
}

std::list<plz::Data> plz::LinkDescriptor::getData() const {
	std::list<Data> ld{};
	Data d;
	while (_data >> d)
		ld.push_back(std::move(d));
	return std::move(ld);
}

bool plz::LinkDescriptor::hasCommand() const {
	return _commands.hasData();
}

bool plz::LinkDescriptor::getCommand(plz::Command &obj)  {
	return _commands >> obj;
}

bool plz::LinkDescriptor::sendCommand(const Command &command) const {
	return _commands && _commands << command;
}

bool plz::LinkDescriptor::sendData(plz::Data data) {
	return _data && _data << data;
}
