##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

BUILD_DIR = build/

all: dir
	@cd $(BUILD_DIR) && \
	cmake $(UI) -DCMAKE_BUILD_TYPE=Release --target plazza ../ && \
	$(MAKE) -s plazza

ui: UI = -DTARGET=graphical
ui: all

clean:
	@if [ -d dir ]; then $(MAKE) -s -C $(BUILD_DIR) clean; fi

fclean: clean
	rm -rf $(BUILD_DIR)
	rm -f plazza

re: fclean all

.PHONY: all clean fclean re
