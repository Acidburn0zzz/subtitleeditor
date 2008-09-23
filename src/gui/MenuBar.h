#ifndef _MenuBar_h
#define _MenuBar_h

/*
 *	subtitleeditor -- a tool to create or edit subtitle
 *
 *	http://home.gna.org/subtitleeditor/
 *	https://gna.org/projects/subtitleeditor/
 *
 *	Copyright @ 2005-2008, kitone
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <gtkmm.h>
#include <map>
#include "Config.h"
#include "Statusbar.h"


class MenuBar : public Gtk::VBox
{
public:
	MenuBar();
	~MenuBar();

	/*
	 *
	 */
	void create(Gtk::Window &window, Statusbar &statusbar);

	/*
	 *
	 */
	void create_ui_from_file();
protected:
	void connect_proxy(const Glib::RefPtr<Gtk::Action> &action, Gtk::Widget *widget);
	
protected:
public:
	Statusbar* m_statusbar;
	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	std::map<Glib::ustring, sigc::connection> m_connections;
};

#endif//_MenuBar_h

