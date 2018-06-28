/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Data
*/

#include "Data.hpp"

std::string plz::Data::serialize() const
{
	std::string ser{startJsonObj};

	ser += "type:";
	ser += std::to_string(static_cast<int>(type));
	ser += sepJson;
	ser += "data:" + startJsonArr;
	for (auto value = _data.begin(); value != _data.end();) {
		ser += "\"" + *value + "\"";
		if ((++value) != _data.end())
			ser += sepJson;
	}
	ser += endJsonArr;
	return ser + endJsonObj;
}

void plz::Data::deserialize(std::string &&data)
{
	size_t i = 0;
	for (; data[i] && data[i] != ':'; i++);
	i++;
	if (!data[i])
		return;
	type = static_cast<InfoType>(data[i] - '0');
	for (; data[i] && data[i] != '"'; i++);
	for (; data[i] && data[i] != endJsonArr; i++) {
		std::string newData;
		if (data[i] == '"') {
			i++;
			for (; data[i] && data[i] != '"'; i++) {
				newData += data[i];
			}
			_data.push_back(newData);
		}
	}
}
