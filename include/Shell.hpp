/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** shell
*/

#ifndef PLAZZA_SHELL_HPP
        #define PLAZZA_SHELL_HPP

#include <unordered_map>
#include <vector>
#include <list>
#include "plazza.hpp"
#include "CLIParser.hpp"

namespace plazza {

        class Shell {
	public:
		Shell();
		~Shell() = default;
		std::list<operation> getCommands();

	private:
		CLIParser _cli;
	};
};

#endif //PLAZZA_SHELL_H
