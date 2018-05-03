/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** my_button
*/

#ifndef PLAZZA_MYBUTTON_HPP
#define PLAZZA_MYBUTTON_HPP


#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

namespace gfx {

	class myButton : public Gtk::Button {
	public:
		myButton(const Glib::ustring& label, bool mnemonic=false);
		~myButton() = default;
		void setMargin(int margin);
	};
}


#endif //PLAZZA_MYBUTTON_HPP
