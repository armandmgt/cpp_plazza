/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Command
*/

#include "Command.hpp"

plz::Command::Command(plz::InfoType type, std::string &&filename)
	: type{type}, filename{filename} {
}

plz::Command::operator bool() const {
	return _invalid;
}
