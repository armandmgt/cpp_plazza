/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Serializable
*/

#pragma once

#include <string>

namespace plz {

	auto startJsonObj = '{';
	auto endJsonObj = '}';

	auto startJsonArr = '[';
	auto endJsonArr = ']';

	auto sepJson = ',';

	class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual std::string serialize() = 0;
		virtual void deserialize(std::string &&data) = 0;
	};
}
