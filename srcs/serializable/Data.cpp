/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Data
*/

#include "Data.hpp"

plz::Data::Data(plz::InfoType type, std::list<std::string> &&data) : type{type}, data{std::move(data)} {
}

std::string plz::Data::serialize() const
{
	std::string ser{startJsonObj};

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

void plz::Data::deserialize(std::string &&obj)
{
	size_t i = 0;
	for (; obj[i] && obj[i] != ':'; i++);
	i++;
	if (!obj[i])
		return;
	type = static_cast<InfoType>(obj[i] - '0');
	for (; obj[i] && obj[i] != '"'; i++);
	for (; obj[i] && obj[i] != endJsonArr; i++) {
		std::string newData;
		if (obj[i] == '"') {
			i++;
			for (; obj[i] && obj[i] != '"'; i++) {
				newData += obj[i];
			}
			data.push_back(newData);
		}
	}
}
