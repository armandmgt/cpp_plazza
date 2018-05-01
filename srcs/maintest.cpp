#include "Shell.hpp"
#include <iostream>
#include "Exceptions.hpp"

int main(int argc, char const *argv[])
{
	plazza::Shell *sh = new plazza::Shell();
	while (1) {
		try {
		sh->getInputMap();
		} catch (ArgumentError const &e) {
			std::cout << e.what() << std::endl;
			return 84;
		}
		// }
		// for (auto it : sh->getInputMap()) {
		// 	std::cout << it.first << "  " << it.second << std::endl;
	}
	return 0;
}