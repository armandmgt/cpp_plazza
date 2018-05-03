/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#ifndef PLAZZA_GRAPHIC_HPP
	#define PLAZZA_GRAPHIC_HPP

	#include <array>
	#include <gtkmm.h>
	#include <gtkmm/button.h>
	#include <gtkmm/window.h>
	#include <gtkmm/application.h>
	#include "MyButton.hpp"
	#include "plazza.hpp"

	namespace gfx {

		class Graphic  : public Gtk::Window {
		public:
			Graphic();
			virtual ~Graphic();

			virtual void onButtonClicked();
			virtual void onChooseFile();
			virtual void selectFile();
			virtual void onButtonShowProcess();

		protected:

			plazza::InfoType typeLastFile;
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

			Gtk::Frame m_LeftFrame;
			Gtk::Frame m_RightFrame;
			Gtk::Label m_LabelTittle;
			Gtk::Label m_LeftLabel;
			Gtk::Label m_RightLabel;

		private:
			std::vector<std::string> selectedFiles;
			void setWindow();
			void setBoxInputCmdLine();
			void setBoxLeft();
		};
	}

#endif
