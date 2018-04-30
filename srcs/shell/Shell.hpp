/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** shell
*/

#ifndef PLAZZA_SHELL_HPP
        #define PLAZZA_SHELL_HPP

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "Master.hpp"

namespace plazza {
        class Shell {
                public:
                        Shell();
                        ~Shell();
                        unordered_map<plazza::InfoType, std::string> getInputMap();
                private:
	                void parseCLIInput(std::vector<std::string> const &_cli);
	                void storeInputToMap(std::string &line, InfoType &type);
                        unordered_map<plazza::InfoType, std::string> _input;
                        std::vector<std::string> _cli;
                        std::unordered_map<std::string, plazza::InfoType> _type;
        };
};

#endif //PLAZZA_SHELL_H
