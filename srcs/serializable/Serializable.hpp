/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Serializable
*/

#pragma once

#include <string>

namespace plz {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		virtual std::string serialize() = 0;
		virtual void deserialize() = 0;
	};
}
