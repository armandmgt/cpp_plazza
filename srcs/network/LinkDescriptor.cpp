/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, LinkDescriptor
*/

#include "LinkDescriptor.hpp"

plz::LinkDescriptor::LinkDescriptor(int sCommand, int sData, int sRequest, int sInfo)
	: commands{sCommand}, data{sData}, requests{sRequest}, infos{sInfo} {
}

bool plz::LinkDescriptor::isAlive() {
	return false;
}

bool plz::LinkDescriptor::send(const plz::ISerializable &data) {
	return false;
}

bool plz::LinkDescriptor::hasData() const {
	return false;
}
