/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, SocketStream
*/

#pragma once

#include <queue>
#include "serializable/Serializable.hpp"

namespace plz {
	class SocketStream {
	public:
		explicit SocketStream(int socket);
		~SocketStream();

		bool hasData() const;
		bool operator<<(Serializable const &obj) const;
		template<typename T>
		bool operator>>(T &obj) const {
			static_assert(std::is_base_of<Serializable, T>(), "Cannot deserialize, T is not a valid type");
			if (!hasData())
				return false;
			obj.deserialize("");
			return true;
		}

	private:
		int socket;
		mutable std::queue<std::string> buffer{};
	};
}
