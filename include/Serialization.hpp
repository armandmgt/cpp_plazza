/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Serialization
*/

#ifndef PLAZZA_SERIALIZATION_HPP
	#define PLAZZA_SERIALIZATION_HPP

	#include <poll.h>
	#include <cstring>
	#include <cerrno>
	#include <sys/socket.h>
	#include "Exceptions.hpp"

	namespace plazza {
		template<typename T>
		int operator>>(int sd, T &data) {
			struct pollfd pfd = {sd, POLLIN, 0};

			switch (poll(&pfd, 1, 1000)) {
				case -1:
					throw RuntimeError(strerror(errno));
				case 0:
					break;
				default:
					recv(sd, &data, sizeof(data), MSG_DONTWAIT);
					break;
			}
			return sd;
		}

		template<typename T>
		int operator<<(int sd, T const &data) {
			if (send(sd, &data, sizeof(data), 0) == -1)
				throw RuntimeError(strerror(errno));
			return sd;
		}
	}

#endif //PLAZZA_SERIALIZATION_HPP
