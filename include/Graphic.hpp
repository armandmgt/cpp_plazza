/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#ifndef PLAZZA_GRAPHIC_HPP
	#define PLAZZA_GRAPHIC_HPP

	#include <array>
	#include <vector>
	#include <gtkmm.h>
	#include <gtkmm/button.h>
	#include <gtkmm/window.h>
	#include <gtkmm/application.h>
	#include <filesystem>
	#include "MyButton.hpp"
	#include "Master.hpp"
	#include "Frame.hpp"

	namespace gfx {

		struct elem {
			std::chrono::steady_clock::time_point timer;
			Gtk::ProgressBar progress;
			Gtk::Label label;
		};

		class Graphic  : public Gtk::Window {
		public:
			explicit Graphic(int nbThread);

			virtual void onButtonClicked();
			virtual void onChosenFile();
			virtual void selectFile();
			virtual void onButtonShowProcessIpAddr();
			virtual void onButtonShowProcessEmail();
			virtual void onButtonShowProcessPhone();

		protected:
			Gtk::Box m_principalBox;

			std::array<Gtk::Box, 2> m_secondBox;
			std::array<Gtk::Box, 2> m_thirdBox;
			Gtk::Box DisplayBox;
			Gtk::Box m_buttonBox;

			myButton m_chooseFile;
			myButton m_Close;
			myButton m_buttonIpAddr;
			myButton m_buttonPhone;
			myButton m_buttonEmail;

			MyFrame m_LeftFrame;
			MyFrame m_RightFrame;
			Gtk::Label m_LabelTittle;
			Gtk::Label m_LeftLabel;
			Gtk::Grid m_GridProgress;
		private:
			plz::Master masterProcess;
			std::unordered_map<std::string, elem> allProgressBar;
			std::vector<std::string> selectedFiles;
			void setWindow();
			void setBoxInputCmdLine();
			void setBoxLeft();
			void setProgressBar(std::string &name, int pos);
		};
	}

#endif
