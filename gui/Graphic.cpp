/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "Graphic.hpp"

gfx::fileManager::fileManager() : m_validate("Validate")
{
	set_border_width(100);
	m_validate.signal_clicked().connect(sigc::mem_fun(*this,
							&fileManager::on_button_clicked));
	add(m_validate);
	m_validate.show();
	set_title("plazza");
	set_title("plazza");
	set_role("plazza");

}

gfx::fileManager::~fileManager()
{
}

void gfx::fileManager::on_button_clicked()
{
	std::cout << "Push button" << std::endl;
}

int main(int ac, char **av)
{
	auto app = Gtk::Application::create(ac, av, "org.gtkmm.examples.base");
	gfx::fileManager application;
	application.set_position(Gtk::WIN_POS_CENTER);

	return 	app->run(application);
}
