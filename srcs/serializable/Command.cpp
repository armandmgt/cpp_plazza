/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Command
*/

#include <string>
#include "Command.hpp"

std::string plz::Command::serialize()
{
	std::string ser("" + startJsonObj);

	ser += "type:";
	ser += std::to_string(static_cast<int>(type));
	ser += sepJson;
	ser += "filename:";
	ser += "\"" + filename + "\"";
	return ser + endJsonObj;
}

void plz::Command::deserialize(std::string &&data)
{

}
