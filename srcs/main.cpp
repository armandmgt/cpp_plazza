/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main
*/

#include <exception>
#include <iostream>
#ifdef GRAPHICAL
#include <gtkmm/application.h>
#endif
#include "plazza.hpp"
#include "Master.hpp"
#ifdef GRAPHICAL
#include "Graphic.hpp"
#endif

int main(int argc, char const *argv[])
{
	if (check_args(argc, argv)) {
    		return (FAILURE);
	} else {
		try {
		#ifdef GRAPHICAL
			auto app = Gtk::Application::create("org.gtkmm.examples.base");
			gfx::Graphic application(std::stoi(argv[1]));
			application.set_position(Gtk::WIN_POS_CENTER);
			return 	app->run(application);
		#else
			plazza::Master m(std::stoi(argv[1]));
			m.runMaster();
		#endif
		} catch (std::exception const &e) {
			std::cerr << e.what() << std::endl;
			return (FAILURE);
		}
		return (SUCCESS);
	}
}