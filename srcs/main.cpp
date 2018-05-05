/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include <exception>
#include <iostream>
#include "plazza.hpp"
#include "Master.hpp"

int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	if (check_args(argc, argv)) {
    		return (FAILURE);
	} else {
		try {
			plazza::Master m(std::stoi(argv[1]));
			m.runMaster();
		} catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			return (FAILURE);
		}
		return (SUCCESS);
	}
}