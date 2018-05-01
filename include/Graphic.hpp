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

	namespace gfx {

		class fileManager  : public Gtk::Window {
		public:
			fileManager();
			virtual ~fileManager();

			virtual void on_button_clicked();


		protected:
			Gtk::Button m_validate;
		};
	}

#endif
