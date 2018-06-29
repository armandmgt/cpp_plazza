/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#pragma once

#include "network/LinkDescriptor.hpp"

namespace plz {
	class Slave {
	public:
		explicit Slave(plz::LinkDescriptor &&descriptor);

		void exec();

	private:
		LinkDescriptor master;
	};
}
