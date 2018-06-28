/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, LinkDescriptor
*/

#pragma once

#include <queue>
#include "serializable/ISerializable.hpp"
#include "SocketStream.hpp"

namespace plz {
	class LinkDescriptor {
	public:
		LinkDescriptor() = default;
		LinkDescriptor(int sCommand, int sData, int sRequest, int sInfo);

		bool isAlive();
		bool send(ISerializable const &data);
		bool hasData() const;
		template<typename T>
		T receive() {
			return T{};
		}

	private:
		SocketStream commands{ -1 };
		SocketStream data{ -1 };
		SocketStream requests{ -1 };
		SocketStream infos{ -1 };
		std::queue<std::string> buffer{};
	};

	LinkDescriptor createSlave();
}
