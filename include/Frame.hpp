/*
** EPITECH PROJECT, 2018
** plazzaui
** File description:
** Frame
*/
#ifndef PLAZZAUI_FRAME_HPP
#define PLAZZAUI_FRAME_HPP


#include <gtkmm/frame.h>

	class MyFrame : public Gtk::Frame {
	public:
		MyFrame(const Glib::ustring& label);
		MyFrame();
		~MyFrame() = default;

		void setMargin(int margin);
	};


#endif //PLAZZAUI_FRAME_HPP
