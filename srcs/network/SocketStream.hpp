/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, SocketStream
*/

#pragma once

#include <queue>
#include "serializable/ISerializable.hpp"

namespace plz {
	class SocketStream {
	public:
		explicit SocketStream(int socket);
		~SocketStream();

		bool hasData() const;
		bool operator<<(ISerializable const &obj) const;
		template<typename T>
		bool operator>>(T &obj) const;

		explicit operator bool() const;

	private:
		mutable int _socket;
		mutable std::queue<std::string> _buffer{};

		std::string getLine() const;
	};

	template<typename T>
	bool SocketStream::operator>>(T &obj) const {
		static_assert(std::is_base_of<ISerializable, T>(), "Cannot deserialize, T is not a valid type");
		auto &&line = getLine();
		obj.deserialize(std::move(line));
		return true;
	}
}
