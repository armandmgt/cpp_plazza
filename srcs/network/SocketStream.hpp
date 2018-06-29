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
		SocketStream() = default;
		explicit SocketStream(int socket);
		SocketStream(SocketStream const &rhs) = delete;
		SocketStream(SocketStream &&rhs) noexcept;
		~SocketStream();

		SocketStream &operator =(SocketStream const &rhs) = delete;
		SocketStream &operator =(SocketStream &&rhs) noexcept;

		bool hasData() const;
		bool operator<<(ISerializable const &obj) const;
		template<typename T>
		bool operator>>(T &obj) const;

		explicit operator bool() const;

	private:
		mutable int _socket{ -1 };
		mutable std::queue<std::string> _buffer{};

		bool getLine(std::string &string) const;
	};

	template<typename T>
	bool SocketStream::operator>>(T &obj) const {
		static_assert(std::is_base_of<ISerializable, T>(), "Cannot deserialize, T is not a valid type");
		std::string line;
		if (!getLine(line))
			return false;
		obj.deserialize(std::move(line));
		return true;
	}
}
