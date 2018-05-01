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

		typedef enum e_CLI_Mode {
			DRAG_AND_DROP,
			CMD_LINE
		} CLI_Mode;

		class fileManager  : public Gtk::Window {
		public:
			fileManager();
			virtual ~fileManager();

			virtual void on_button_clicked();
			virtual void changeMode();
			virtual void on_icon_pressed(Gtk::EntryIconPosition, const GdkEventButton *);


		protected:
			Gtk::Box m_Box;
			Gtk::Entry m_Entry;
			Gtk::Button m_mode;
			Gtk::Button m_validate;
		private:
			CLI_Mode mode = CMD_LINE;
			void setWindow();
			void setBoxInputCmdLine();
		};
	}

#endif
