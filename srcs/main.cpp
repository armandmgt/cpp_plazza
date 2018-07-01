/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main 192.168.1.1
*/

#include <exception>
#include <iostream>
#ifdef GRAPHICAL
# include <gtkmm/application.h>
#endif
#include "master/Master.hpp"
#include "constants.hpp"

#ifdef GRAPHICAL
# include "../include/Graphic.hpp"
#endif

int main(int argc, char const *argv[])
{
	if (argc < 2)
		return FAILURE;
	try {
		#ifdef GRAPHICAL
			auto app = Gtk::Application::create("org.gtkmm.examples.base");
			gfx::Graphic application(std::stoi(argv[1]));
			application.set_position(Gtk::WIN_POS_CENTER);
			return app->run(application);
		#else
			plz::Master m(static_cast<unsigned>(std::stoul(argv[1])));
			m.run();
		#endif
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}