/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Data
*/

#include "Data.hpp"

std::string plz::Data::serialize()
{
	std::string ser("" + startJsonObj);

	ser += "type:";
	ser += std::to_string(static_cast<int>(type));
	ser += sepJson;
	ser += "data:" + startJsonArr;
	for (auto value = data.begin(); value != data.end();) {
		ser += "\"" + *value + "\"";
		if ((++value) != data.end())
			ser += sepJson;
	}
	ser += endJsonArr;
	return ser + endJsonObj;
}

void plz::Data::deserialize(std::string &&data)
{

}
