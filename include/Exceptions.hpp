/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Exceptions
*/

#ifndef PLAZZA_EXCEPTIONS_HPP
	#define PLAZZA_EXCEPTIONS_HPP

	#include <exception>

	class ArgumentError : public std::exception
	{
	public:
		explicit ArgumentError(std::string const &message)
		: _msg(message) {}
		const char *what() const noexcept override {
			return _msg.c_str();
		}

	protected:
		std::string const _msg;
	};

	class RuntimeError : public std::runtime_error {
	public:
		explicit RuntimeError(std::string const &message)
		: runtime_error(message), _msg(message) {}
		const char *what() const noexcept override {
			return _msg.c_str();
		}

	protected:
		std::string const _msg;
	};

#endif //PLAZZA_EXCEPTIONS_HPP
