/*
** EPITECH PROJECT, 2017
** Project
** File description:
** Created by armandmgt, Slave
*/

#pragma once

#include "LinkDescriptor.hpp"

namespace plz {
	class Slave {
	public:
		explicit Slave(plz::LinkDescriptor &&descriptor);

	private:
		LinkDescriptor master;
	};
}
