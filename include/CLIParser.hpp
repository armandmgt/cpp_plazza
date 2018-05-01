/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CLIPaser
*/

#ifndef PLAZZA_CLIPARSER_HPP
#define PLAZZA_CLIPARSER_HPP

#include <vector>

namespace plazza {
        class CLIParser {
                public:
                        CLIParser();
                        ~CLIParser();
                        std::vector<std::string> getInput();
                private:
                        std::vector<std::string> _cli;
        };
};

#endif //PLAZZA_CLIPARSER_HPP
