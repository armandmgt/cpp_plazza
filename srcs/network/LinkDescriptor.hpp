/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, LinkDescriptor
*/

#pragma once

#include <queue>
#include "serializable/Serializable.hpp"

namespace plz {
	class LinkDescriptor {
	public:
		LinkDescriptor() = default;
		~LinkDescriptor() = default;

		bool isAlive();
		bool send(Serializable const &data);
		bool hasData() const;
		template<typename T>
		T receive() {
			return T{};
		}

	private:
		int dataSocket{ -1 };
		int commandSocket{ -1 };
		std::queue<std::string> buffer{};
	};
}
