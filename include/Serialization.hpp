/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Serialization
*/

#ifndef PLAZZA_SERIALIZATION_HPP
	#define PLAZZA_SERIALIZATION_HPP

	#include "plazza.hpp"
	#include "Slave.hpp"

	namespace plazza {
		int operator>>(int sd, plazza::command &cmd);
		int operator<<(int sd, plazza::command &cmd);
		int operator>>(int sd, plazza::Data &cmd);
		int operator<<(int sd, plazza::Data &cmd);
		int operator>>(int sd, plazza::Load &cmd);
		int operator<<(int sd, plazza::Load &cmd);
	}

#endif //PLAZZA_SERIALIZATION_HPP
