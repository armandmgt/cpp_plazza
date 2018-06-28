/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Serializable
*/

#pragma once

#include <string>

namespace plz {

	static const auto startJsonObj = '{';
	static const auto endJsonObj = '}';

	static const auto startJsonArr = '[';
	static const auto endJsonArr = ']';

	static const auto sepJson = ',';

	class ISerializable {
	public:
		virtual ~ISerializable() = default;

		virtual std::string serialize() const = 0;
		virtual void deserialize(std::string &&data) = 0;
	};
}
