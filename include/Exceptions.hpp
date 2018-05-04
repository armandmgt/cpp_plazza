/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Exceptions
*/

#ifndef PLAZZA_EXCEPTIONS_HPP
	#define PLAZZA_EXCEPTIONS_HPP

	#include <exception>
	#include <stdexcept>
	#include <utility>

	class ArgumentError : public std::exception
	{
	public:
		explicit ArgumentError(std::string message)
		: _msg(std::move(message)) {}
		const char *what() const noexcept override {
			return _msg.c_str();
		}

	protected:
		std::string const _msg;
	};

#endif //PLAZZA_EXCEPTIONS_HPP
