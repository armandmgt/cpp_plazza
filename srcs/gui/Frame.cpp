/*
** EPITECH PROJECT, 2018
** plazzaui
** File description:
** Frame
*/
#include "../include/Frame.hpp"

MyFrame::MyFrame(const Glib::ustring &label) : Gtk::Frame(label)
{}

void MyFrame::setMargin(int margin)
{
	set_margin_left(margin);
	set_margin_right(margin);
	set_margin_top(margin);
	set_margin_bottom(margin);
}
