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

		class Graphic  : public Gtk::Window {
		public:
			Graphic();
			virtual ~Graphic();

			virtual void on_button_clicked();
			virtual void changeMode();
			virtual void on_icon_pressed(Gtk::EntryIconPosition, const GdkEventButton *);
			void on_button_drag_data_get(
				const Glib::RefPtr<Gdk::DragContext>&,
				Gtk::SelectionData& selection_data, guint, guint);
			void on_label_drop_drag_data_received(
				const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
				const Gtk::SelectionData& selection_data, guint info, guint time);

		protected:
			Gtk::Box m_inputBox;
			Gtk::Box m_buttonBox;
			Gtk::Box m_dragDrop;
			Gtk::Entry m_Entry;
			Gtk::Button m_mode;
			Gtk::Button m_validate;
			Gtk::Button m_Button_Drag;
			Gtk::Label m_Label_Drop;
		private:
			CLI_Mode mode = CMD_LINE;
			void setWindow();
			void initDragAndDrop();
			void setBoxInputCmdLine();
		};
	}

#endif
