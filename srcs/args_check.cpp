/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** args_check
*/

#include <string>
#include <iostream>
#include "Exceptions.hpp"
#include "plazza.hpp"

int check_args(int argc, char const *argv[])
{
	if (argc != 2) {
		return 1;
	}
	try {
		int i = std::stoi(argv[1]);
		if (i <= 0)
			throw ArgumentError("The number of threads must be "
		       "a positive integer");
	} catch (ArgumentError const &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}