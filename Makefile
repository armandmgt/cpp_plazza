##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

all:
    cmake -DCMAKE_BUILD_TYPE=Release

fclean:
    rm -f plazza

re: fclean all

.PHONY: all clean fclean re
