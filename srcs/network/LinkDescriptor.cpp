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

bool plz::LinkDescriptor::send(const plz::ISerializable &data[[maybe_unused]]) {
	return _data << data;
}

bool plz::LinkDescriptor::hasData() const {
	return false;
}
