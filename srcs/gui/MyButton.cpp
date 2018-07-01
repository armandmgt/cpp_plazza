/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** my_button
*/

#include "../include/MyButton.hpp"


gfx::myButton::myButton(const Glib::ustring& label, bool mnemonic) :
	Gtk::Button(label, mnemonic)
{
}

void gfx::myButton::setMargin(int margin)
{
	set_margin_left(margin);
	set_margin_right(margin);
	set_margin_top(margin);
	set_margin_bottom(margin);
}