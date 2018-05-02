/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "Graphic.hpp"

gfx::Graphic::Graphic() : m_inputBox(Gtk::ORIENTATION_VERTICAL),
			  m_buttonBox(Gtk::ORIENTATION_HORIZONTAL),
			  	m_chooseFile("Choose File"),
				m_validate("Validate")

{
	setWindow();
	add(m_inputBox);
	setBoxInputCmdLine();
	show_all_children();
}

gfx::Graphic::~Graphic()
{
}

void gfx::Graphic::setWindow()
{
	set_default_size(1280, 720);
	set_border_width(10);
	set_title("plazza");
	set_role("plazza");
}

void gfx::Graphic::setBoxInputCmdLine()
{
	m_buttonBox.pack_start(m_chooseFile);
	m_buttonBox.pack_start(m_validate);
	m_inputBox.pack_end(m_buttonBox, Gtk::PACK_SHRINK);
	m_validate.signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::onButtonClicked));
	m_chooseFile.signal_clicked().connect(sigc::mem_fun(*this,
							  &Graphic::onChooseFile));
	m_validate.set_size_request(10, 10);
	m_validate.show();
	m_chooseFile.show();
}

void gfx::Graphic::onButtonClicked()
{
	std::cout << "Start Process" << std::endl;
}

void gfx::Graphic::selectFile()
{
	std::cout << "Selected file" << std::endl;
}

void gfx::Graphic::onChooseFile()
{
	Gtk::FileChooserDialog dialog("Please choose a folder",
				      Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_select_multiple();
	dialog.set_transient_for(*this);
	dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
	Gtk::Button *select = dialog.add_button("Select", Gtk::RESPONSE_OK);
	select->signal_clicked().connect(sigc::mem_fun(*this,
							    &Graphic::selectFile));
	int result = dialog.run();
	if (result == Gtk::RESPONSE_OK) {
		auto allFileName = dialog.get_filenames();
		for (unsigned int i = 0; i < allFileName.size(); i++) {
			std::cout << "File selected: " << allFileName[i]
				  << std::endl;
		}
	}
}

int main(int ac, char **av)
{
	auto app = Gtk::Application::create(ac, av, "org.gtkmm.examples.base");
	gfx::Graphic application;
	application.set_position(Gtk::WIN_POS_CENTER);

	return 	app->run(application);
}
