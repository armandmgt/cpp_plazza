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
		Data(InfoType type, std::list<std::string> &&data);

		std::string serialize() const final;
		void deserialize(std::string &&obj) final;
		InfoType type{};
		std::list<std::string> data{};
	};
}
