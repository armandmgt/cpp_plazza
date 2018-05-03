/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "Graphic.hpp"

gfx::Graphic::Graphic(int nbThread) : m_principalBox(Gtk::ORIENTATION_VERTICAL),
			  	m_chooseFile("Choose File"),
				m_Close("Close"),
			  m_buttonIpAddr("IP_ADDR"),
			  m_buttonPhone("PHONE_NUMBER"),
			  m_buttonEmail("EMAIL_ADDR"),
			  m_LeftFrame("Chosen Files"),
			  m_RightFrame("Process")
{
	static_cast<void>(nbThread);
	setWindow();
	m_secondBox[0].set_orientation(Gtk::ORIENTATION_VERTICAL);
	m_secondBox[1].set_orientation(Gtk::ORIENTATION_VERTICAL);
	DisplayBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	add(m_principalBox);
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
	m_LabelTittle.set_markup("<b>Selected Files</b>");
	set_title("plazza");
	set_role("plazza");
}

void gfx::Graphic::setBoxLeft()
{
	m_secondBox[0].pack_start(m_thirdBox[0]);
	m_secondBox[0].pack_end(m_thirdBox[1], Gtk::PACK_SHRINK);
	m_thirdBox[0].pack_start(m_LeftFrame);
	m_LeftFrame.add(m_LeftLabel);
	m_LeftFrame.set_label_align(0.01, 0.5);
	m_buttonIpAddr.signal_clicked().connect(sigc::mem_fun(*this,
							      &Graphic::onButtonShowProcess));
	m_buttonPhone.signal_clicked().connect(sigc::mem_fun(*this,
							      &Graphic::onButtonShowProcess));
	m_buttonEmail.signal_clicked().connect(sigc::mem_fun(*this,
							      &Graphic::onButtonShowProcess));
	m_buttonIpAddr.setMargin(10);
	m_thirdBox[1].pack_start(m_buttonIpAddr);
	m_buttonPhone.setMargin(10);
	m_thirdBox[1].pack_start(m_buttonPhone);
	m_buttonEmail.setMargin(10);
	m_thirdBox[1].pack_start(m_buttonEmail);
}

void gfx::Graphic::setBoxInputCmdLine()
{
	m_principalBox.pack_start(m_LabelTittle, Gtk::PACK_SHRINK);
	m_principalBox.pack_start(DisplayBox, Gtk::PACK_EXPAND_WIDGET);
	m_principalBox.pack_end(m_buttonBox, Gtk::PACK_SHRINK);
	DisplayBox.pack_start(m_secondBox[0], Gtk::PACK_EXPAND_WIDGET);
	DisplayBox.pack_start(m_secondBox[1], Gtk::PACK_EXPAND_WIDGET);
	m_buttonBox.pack_start(m_Close);
	m_Close.setMargin(10);
	m_buttonBox.pack_start(m_chooseFile);
	m_chooseFile.setMargin(10);
	setBoxLeft();
	m_secondBox[1].pack_start(m_RightFrame);
	m_Close.signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::onButtonClicked));
	m_chooseFile.signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::onChooseFile));
	m_RightFrame.set_label_align(0.02, 0.5);
	m_RightFrame.setMargin(5);
	m_LeftFrame.setMargin(5);
	m_Close.show();
	m_chooseFile.show();
}

void gfx::Graphic::onButtonClicked()
{
	hide();
}

void gfx::Graphic::onButtonShowProcess()
{
	selectedFiles.clear();
	std::cout << "Start Process" << std::endl;
}


void gfx::Graphic::selectFile()
{
}

void gfx::Graphic::onChooseFile()
{
	std::string filesName;
	Gtk::FileChooserDialog dialog("Please choose files",
				      Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_select_multiple();
	filesName.clear();
	m_LeftLabel.set_text("");
	dialog.set_transient_for(*this);
	dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
	Gtk::Button *select = dialog.add_button("Select", Gtk::RESPONSE_OK);
	select->signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::selectFile));
	int result = dialog.run();
	if (result == Gtk::RESPONSE_OK) {
		auto allFileName = dialog.get_filenames();
		for (unsigned int i = 0; i < allFileName.size(); i++) {
			if (!std::filesystem::is_directory(allFileName[i])) {
				filesName += allFileName[i] + "\n";
				selectedFiles.push_back(allFileName[i]);
			}
		}
		m_LeftLabel.set_text(m_LeftLabel.get_text() + filesName);
	}
}

int main(int ac, char **av)
{
	auto app = Gtk::Application::create("org.gtkmm.examples.base");
	if (ac != 2) {
		std::cout << "./" << av[0] << " [nbThread by Process]" << std::endl;
		return 84;
	}
	try {
		gfx::Graphic application(std::stoi(av[1]));
		application.set_position(Gtk::WIN_POS_CENTER);
		return 	app->run(application);
k	} catch (std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
		return 84;
	}


}
