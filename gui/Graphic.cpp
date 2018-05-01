/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "Graphic.hpp"

gfx::fileManager::fileManager() : m_Box(Gtk::ORIENTATION_VERTICAL),
				  m_mode("Drag & Drop"),
				  m_validate("Validate")
{
	setWindow();
	add(m_Box);
	setBoxInputCmdLine();
	show_all_children();
}

gfx::fileManager::~fileManager()
{
}

void gfx::fileManager::setWindow()
{
	set_default_size(1280, 720);
	set_border_width(10);
	set_title("plazza");
	set_role("plazza");
}

void gfx::fileManager::setBoxInputCmdLine()
{
	m_Box.pack_start(m_Entry, Gtk::PACK_SHRINK);
	m_Box.pack_start(m_mode, Gtk::PACK_SHRINK);
	m_Box.pack_start(m_validate, Gtk::PACK_SHRINK);
	m_mode.signal_clicked().connect(sigc::mem_fun(*this,
							  &fileManager::changeMode));
	m_validate.signal_clicked().connect(sigc::mem_fun(*this,
							  &fileManager::on_button_clicked));
	m_Entry.set_max_length(258);
	m_Entry.set_icon_from_icon_name("edit-find");
	m_Entry.signal_icon_press().connect(sigc::mem_fun(*this,
							  &fileManager::on_icon_pressed));
	m_validate.set_size_request(10, 10);
	m_validate.show();
	m_mode.show();
	m_Entry.show();
}

void gfx::fileManager::on_icon_pressed(Gtk::EntryIconPosition iconPosition, const GdkEventButton* button)
{
	(void)iconPosition;
	(void)button;
	std::cout << m_Entry.get_text() << std::endl;
}

void gfx::fileManager::on_button_clicked()
{
	std::cout << m_Entry.get_text() << std::endl;
}

void gfx::fileManager::changeMode()
{
	if (mode == CMD_LINE) {
		m_mode.set_label("Drag & Drop");
		mode = DRAG_AND_DROP;
	} else if (mode == DRAG_AND_DROP) {
		m_mode.set_label("Command Line");
		mode = CMD_LINE;
	}
}

int main(int ac, char **av)
{
	auto app = Gtk::Application::create(ac, av, "org.gtkmm.examples.base");
	gfx::fileManager application;
	application.set_position(Gtk::WIN_POS_CENTER);

	return 	app->run(application);
}
