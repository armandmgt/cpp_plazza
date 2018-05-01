/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CLIPaser
*/

#ifndef PLAZZA_CLIPARSER_HPP
#define PLAZZA_CLIPARSER_HPP

#include <vector>
#include "Shell.hpp"

namespace plazza {
        class CLIParser {
                public:
                        CLIParser();
                        ~CLIParser();
                        std::vector<std::string> getCLI();
                private:
                        std::vector<std::string> _cli;
        };
};

#endif //PLAZZA_CLIPARSER_HPP