/*
** EPITECH PROJECT, 2017
** plazza
** File description:
** Created by armandmgt, Master
*/

#include "Master.hpp"

plz::Master::Master(unsigned nbThreads) : _nbThreads{nbThreads} {
}

void plz::Master::run() {
	while (true) {
		auto command = _parser.getLine();
		if (!command)
			return;
	}
}
