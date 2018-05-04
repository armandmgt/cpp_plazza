/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include <exception>
#include <Master.hpp>
#include <iostream>
#include "plazza.hpp"

int main(int argc, char const *argv[])
{
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