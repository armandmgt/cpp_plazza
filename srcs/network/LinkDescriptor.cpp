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
	return std::list<plz::Data>{};
}

bool plz::LinkDescriptor::hasCommand() const {
	return _commands.hasData();
}

bool plz::LinkDescriptor::sendCommand(const Command &command) const {
	return _commands && _commands << command;
}
