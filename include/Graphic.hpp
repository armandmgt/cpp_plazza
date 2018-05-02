/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#ifndef PLAZZA_GRAPHIC_HPP
	#define PLAZZA_GRAPHIC_HPP

	#include <gtkmm.h>
	#include <gtkmm/button.h>
	#include <gtkmm/window.h>
	#include <gtkmm/application.h>
	#include "plazza.hpp"

	namespace gfx {

		class Graphic  : public Gtk::Window {
		public:
			Graphic();
			virtual ~Graphic();

			virtual void onButtonClicked();
			virtual void onChooseFile();
			virtual void selectFile();

		protected:

			plazza::InfoType typeLastFile;
			Gtk::Box m_inputBox;
			Gtk::Box m_buttonBox;
			Gtk::Button m_chooseFile;
			Gtk::Button m_validate;

		private:
			void setWindow();
			void setBoxInputCmdLine();
		};
	}

#endif
