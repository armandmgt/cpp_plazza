/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, LinkDescriptor
*/

#pragma once

#include <queue>
#include "serializable/Data.hpp"
#include "serializable/Command.hpp"
#include "serializable/ISerializable.hpp"
#include "SocketStream.hpp"

namespace plz {
	class LinkDescriptor {
	public:
		LinkDescriptor() = default;
		LinkDescriptor(int sCommand, int sData, int sRequest, int sInfo);

		bool isAlive();
		bool sendCommand(const Command &command) const;
//		bool sendRequest(Request request) const;
//		WorkLoad getInfos() const;
		bool hasData() const;
		std::list<Data> getData() const;
		bool hasCommand() const;
		bool getCommand(Command &obj);

		bool sendData(Data data);

	private:
		SocketStream _commands{ -1 };
		SocketStream _data{ -1 };
		SocketStream _requests{ -1 };
		SocketStream _infos{ -1 };
	};

	plz::LinkDescriptor createSlave(unsigned nbThread);
}
