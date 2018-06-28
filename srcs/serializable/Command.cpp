/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Command
*/

#include <string>
#include "Command.hpp"

std::string plz::Command::serialize() const
{
	std::string ser{startJsonObj};

	ser += "type:";
	ser += std::to_string(static_cast<int>(type));
	ser += sepJson;
	ser += "filename:";
	ser += "\"" + filename + "\"";
	return ser + endJsonObj;
}

void plz::Command::deserialize(std::string &&data)
{
	size_t i = 0;
	for (; data[i] && data[i] != ':'; i++);
	i++;
	if (!data[i])
		return;
	type = static_cast<InfoType>(data[i] - '0');
	for (; data[i] && data[i] != '"'; i++);
	for (; data[i] && data[i] != '"'; i++) {
		filename += data[i];
	}
}
