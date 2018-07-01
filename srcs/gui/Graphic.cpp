/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "../include/Shell.hpp"
#include "../include/Utils.hpp"
#include "../include/Graphic.hpp"

gfx::Graphic::Graphic(int nbThread)
	: masterProcess(nbThread), m_principalBox(Gtk::ORIENTATION_VERTICAL),
	  m_chooseFile("Choose File"), m_Close("Close"),
	  m_buttonIpAddr("IP_ADDRESS"), m_buttonPhone("PHONE_NUMBER"),
	  m_buttonEmail("EMAIL_ADDRESS"), m_LeftFrame("Chosen Files"),
	  m_RightFrame("Process")
{
	setWindow();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_secondBox[0].set_orientation(Gtk::ORIENTATION_VERTICAL);
	m_secondBox[1].set_orientation(Gtk::ORIENTATION_VERTICAL);
	DisplayBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	add(m_principalBox);
	setBoxInputCmdLine();
	show_all_children();
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
	m_LeftFrame.set_label_align(0.02, 0.5);
	m_buttonIpAddr.signal_clicked().connect(sigc::mem_fun(*this, &Graphic::onButtonShowProcessIpAddr));
	m_buttonPhone.signal_clicked().connect(sigc::mem_fun(*this, &Graphic::onButtonShowProcessPhone));
	m_buttonEmail.signal_clicked().connect(sigc::mem_fun(*this, &Graphic::onButtonShowProcessEmail));
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
	m_Close.signal_clicked().connect(sigc::mem_fun(*this, &Graphic::onButtonClicked));
	m_chooseFile.signal_clicked().connect(sigc::mem_fun(*this, &Graphic::onChosenFile));
	m_RightFrame.set_label_align(0.02, 0.5);
	m_RightFrame.setMargin(5);
	m_RightFrame.add(m_GridProgress);
	m_GridProgress.set_row_homogeneous(true);
	m_GridProgress.set_column_homogeneous(true);
	m_LeftFrame.setMargin(5);
	m_Close.show();
	m_chooseFile.show();
}

void gfx::Graphic::onButtonClicked()
{
	hide();
}

void gfx::Graphic::onButtonShowProcessIpAddr()
{
	plazza::shellInput inputShell;
	for (auto const &it : selectedFiles)
		inputShell.push_back({plazza::IP_ADDRESS, it});
	for (auto &it : allProgressBar) {
		it.second.label.show();
		it.second.progress.show();
	}
	for (float i = 0.0; i <= 100.0; i++) {
		for (auto &it : allProgressBar) {
			it.second.progress.set_fraction(i / 100.0);
		}
		while (Gtk::Main::events_pending()) Gtk::Main::iteration(false);
		std::this_thread::sleep_for(std::chrono::microseconds(std::rand() % 500 + 10000));
	}
	masterProcess.distributeIllegalWork(inputShell);
}

void gfx::Graphic::onButtonShowProcessEmail()
{
	plazza::shellInput inputShell;

	for (const auto &it : selectedFiles)
		inputShell.push_back({plazza::EMAIL_ADDRESS, it});
	for (auto &it : allProgressBar) {
		it.second.label.show();
		it.second.progress.show();
	}
	for (float i = 0.0; i <= 100.0; i++) {
		for (auto &it : allProgressBar) {
			it.second.progress.set_fraction(i / 100.0);
		}
		while (Gtk::Main::events_pending()) Gtk::Main::iteration(false);
		std::this_thread::sleep_for(std::chrono::microseconds(std::rand() % 500 + 10000));
	}
	masterProcess.distributeIllegalWork(inputShell);
}

void gfx::Graphic::onButtonShowProcessPhone()
{
	plazza::shellInput inputShell;
	for (const auto &it : selectedFiles)
		inputShell.push_back({plazza::PHONE_NUMBER, it});
	for (auto &it : allProgressBar) {
		it.second.label.show();
		it.second.progress.show();
	}
	for (float i = 0.0; i <= 100.0; i++) {
		for (auto &it : allProgressBar) {
			it.second.progress.set_fraction(i / 100.0);
		}
		while (Gtk::Main::events_pending()) Gtk::Main::iteration(false);
		std::this_thread::sleep_for(std::chrono::microseconds(std::rand() % 500 + 10000));
	}
	masterProcess.distributeIllegalWork(inputShell);
}

void gfx::Graphic::selectFile()
{
}

void gfx::Graphic::onChosenFile()
{
	std::string filesName;
	Gtk::FileChooserDialog dialog("Please choose files", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_select_multiple();
	filesName.clear();
	selectedFiles.clear();
	allProgressBar.clear();
	m_LeftLabel.set_text("");
	dialog.set_transient_for(*this);
	dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
	Gtk::Button *select = dialog.add_button("Select", Gtk::RESPONSE_OK);
	select->signal_clicked().connect(sigc::mem_fun(*this, &Graphic::selectFile));
	int result = dialog.run();
	if (result != Gtk::RESPONSE_OK)
		return;
	auto allFileName = dialog.get_filenames();
	for (unsigned int i = 0; i < allFileName.size(); i++) {
		if (!Filesystem::isDirectory(allFileName[i])) {
			filesName += allFileName[i] + "\n";
			selectedFiles.emplace_back(allFileName[i]);
			setProgressBar(allFileName[i], i);
		}
	}
	m_LeftLabel.set_text(m_LeftLabel.get_text() + filesName);
}

void gfx::Graphic::setProgressBar(std::string &name, int pos)
{
	allProgressBar.emplace(name, elem());
	allProgressBar[name].timer = std::chrono::steady_clock::now();
	allProgressBar[name].label.set_text(Filesystem::getFilename(name));
	m_GridProgress.attach(allProgressBar[name].label, 0, pos, 1, 1);
	m_GridProgress.attach(allProgressBar[name].progress, 1, pos, 1, 1);
	allProgressBar[name].progress.set_halign(Gtk::ALIGN_CENTER);
	allProgressBar[name].progress.set_valign(Gtk::ALIGN_CENTER);
	allProgressBar[name].progress.set_fraction(0.0);
	allProgressBar[name].label.set_justify(Gtk::JUSTIFY_LEFT);
	allProgressBar[name].progress.hide();
	allProgressBar[name].label.hide();
}
