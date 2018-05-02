/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** graphic
*/

#include <iostream>
#include "Graphic.hpp"

gfx::Graphic::Graphic() : m_inputBox(Gtk::ORIENTATION_VERTICAL),
			  m_buttonBox(Gtk::ORIENTATION_HORIZONTAL),
			  m_dragDrop(Gtk::ORIENTATION_HORIZONTAL),
				  m_mode("Drag & Drop"),
				  m_validate("Validate"),
			  m_Button_Drag("Drag Here\n"),
			  m_Label_Drop("Drop here\n")

{
	setWindow();
	add(m_inputBox);
	setBoxInputCmdLine();
	show_all_children();
}

gfx::Graphic::~Graphic()
{
}

void gfx::Graphic::setWindow()
{
	set_default_size(1280, 720);
	set_border_width(10);
	set_title("plazza");
	set_role("plazza");
}

void gfx::Graphic::initDragAndDrop()
{
	std::vector<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry("STRING"));
	listTargets.push_back(Gtk::TargetEntry("text/plain"));
	m_Button_Drag.drag_source_set(listTargets);
	m_Button_Drag.signal_drag_data_get().connect(sigc::mem_fun(*this,
								   &Graphic::on_button_drag_data_get));
	m_dragDrop.pack_start(m_Button_Drag);

	m_Label_Drop.drag_dest_set(listTargets);
	m_Label_Drop.signal_drag_data_received().connect(sigc::mem_fun(*this,
								       &Graphic::on_label_drop_drag_data_received));
	m_dragDrop.pack_start(m_Label_Drop);
	m_inputBox.pack_start(m_dragDrop, Gtk::PACK_SHRINK);
	m_Label_Drop.hide();
	m_Button_Drag.hide();
	m_dragDrop.hide();
}

void gfx::Graphic::setBoxInputCmdLine()
{
	m_inputBox.pack_start(m_Entry, Gtk::PACK_SHRINK);
	m_buttonBox.pack_start(m_mode);
	m_buttonBox.pack_start(m_validate);
	m_inputBox.pack_end(m_buttonBox, Gtk::PACK_SHRINK);
	m_mode.signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::changeMode));
	m_validate.signal_clicked().connect(sigc::mem_fun(*this,
							&Graphic::on_button_clicked));
	m_Entry.set_max_length(258);
	m_mode.set_size_request(150, 20);
	m_Entry.set_icon_from_icon_name("edit-find");
	m_Entry.signal_icon_press().connect(sigc::mem_fun(*this,
							  &Graphic::on_icon_pressed));
	initDragAndDrop();
	m_validate.set_size_request(10, 10);
	m_validate.show();
	m_mode.show();
	m_Entry.show();
}

void gfx::Graphic::on_icon_pressed(Gtk::EntryIconPosition iconPosition, const GdkEventButton* button)
{
	(void)iconPosition;
	(void)button;
	if (mode == CMD_LINE)
		std::cout << m_Entry.get_text() << std::endl;
}

void gfx::Graphic::on_button_clicked()
{
	if (mode == CMD_LINE)
		std::cout << m_Entry.get_text() << std::endl;
}

void gfx::Graphic::changeMode()
{
	if (mode == CMD_LINE) {
		m_mode.set_label("Command Line");
		m_dragDrop.show();
		m_Entry.hide();
		mode = DRAG_AND_DROP;
	} else if (mode == DRAG_AND_DROP) {
		m_mode.set_label("Drag & Drop");
		m_dragDrop.hide();
		m_Entry.show();
		mode = CMD_LINE;
	}
}

void gfx::Graphic::on_button_drag_data_get(
	const Glib::RefPtr<Gdk::DragContext>&,
	Gtk::SelectionData& selection_data, guint, guint)
{
	selection_data.set(selection_data.get_target(), 8 /* 8 bits format */,
			   (const guchar*)"I'm Data!",
			   9 /* the length of I'm Data! in bytes */);
}

void gfx::Graphic::on_label_drop_drag_data_received(
	const Glib::RefPtr<Gdk::DragContext>& context, int, int,
	const Gtk::SelectionData& selection_data, guint, guint time)
{
	const int length = selection_data.get_length();
	if((length >= 0) && (selection_data.get_format() == 8))
	{
		std::cout << "Received \"" << selection_data.get_data_as_string()
			  << "\" in label " << std::endl;
	}
	m_Label_Drop.set_label(selection_data.get_data_as_string());
	context->drag_finish(false, false, time);
}

int main(int ac, char **av)
{
	auto app = Gtk::Application::create(ac, av, "org.gtkmm.examples.base");
	gfx::Graphic application;
	application.set_position(Gtk::WIN_POS_CENTER);

	return 	app->run(application);
}
