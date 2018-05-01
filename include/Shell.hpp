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
#include "Master.hpp"

namespace plazza {
        class Shell {
                public:
                        Shell();
                        ~Shell() = default;
                        std::unordered_multimap<plazza::InfoType, std::string> getCommands();
                private:
	                void parseCLIInput(std::vector<std::string> const &_cli);
	                void storeInputToMap(std::string const &line, std::pair<const std::string, InfoType> const &type);
			void findTypeInCommand(std::string const &line, std::pair<const std::string, plazza::InfoType> const &type);

			std::unordered_multimap<InfoType, std::string> _input;
                        std::vector<std::string> _cli;
			int _typeChecker;
			std::unordered_map<std::string, InfoType> _type;
        };
};

#endif //PLAZZA_SHELL_H
