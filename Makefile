##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

BUILD_DIR = cmake-build-release/

all: dir
	@cd $(BUILD_DIR) && \
	cmake -DCMAKE_BUILD_TYPE=Release --target plazza ../ && \
	make plazza

tests_run: dir
	@cd $(BUILD_DIR) && \
	cmake -DCMAKE_BUILD_TYPE=Release --target tests_run ../ && \
	make tests_run

dir:
	@mkdir -p $(BUILD_DIR)

clean: dir
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) clean

fclean: clean
	@rm -f plazza

re: fclean all

.PHONY: all clean fclean re
