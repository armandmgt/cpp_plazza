CXX             =       g++

CXXFLAGS        +=      -Wfatal-errors -Wall -Wextra -W -std=c++11 -Wold-style-cast

CPPFLAGS        +=      -I Shell \
			-I CLIParser \
			-I ../include


RM              =       rm -f

NAME            =       test

SRC             =       Shell/Shell.cpp \
			CLIParser/CLIParser.cpp \
			maintest.cpp


OBJ             =       $(SRC:.cpp=.o)
all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME)
clean:
	$(RM) $(OBJ)
fclean:	clean
	$(RM) $(NAME)
re:     fclean all
.PHONY: all clean fclean re⏎
