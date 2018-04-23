/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include <exception>
#include "plazza.hpp"

static void do_nothing()
{
}

int main(int argc, char const *argv[])
{
	if (check_args(argc, argv)) {
    		return (FAILURE);
	} else {
		try {
			do_nothing();
		} catch (std::exception const &e) {
			return (FAILURE);
		}
		return (SUCCESS);
	}
}