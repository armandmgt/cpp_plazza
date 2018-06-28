/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Data
*/

#pragma once

#include <string>
#include <list>
#include "ISerializable.hpp"
#include "enums.hpp"

namespace plz {
	struct Data : public ISerializable{
		Data() = default;

		std::string serialize() final;
		void deserialize(std::string &&data) final;
		InfoType type{};
		std::list<std::string> _data{};
	};
}
