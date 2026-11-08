#include "SuperTask.hpp"
#include "gui/GTask.hpp"
#include "gtkmm/checkbutton.h"
#include "gtkmm/label.h"
#include "gtkmm/signallistitemfactory.h"
#include "gtkmm/singleselection.h"



void TaskWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
	list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::CENTER));
}

void TaskWindow::on_setup_mark(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
	auto check_buttom = Gtk::make_managed<Gtk::CheckButton>();
	check_buttom->set_sensitive(false);
  	list_item->set_child(*check_buttom);
}

void TaskWindow::on_bind_index(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
     	auto col = std::dynamic_pointer_cast<TaskModel>(list_item->get_item());
      if ( !col ) return;

      auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
      if ( !label ) return;

	label->set_text(std::to_string(col->index));
}

void TaskWindow::on_bind_title(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
     	auto col = std::dynamic_pointer_cast<TaskModel>(list_item->get_item());
      if ( !col ) return;

      auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
      if ( !label ) return;

	label->set_text(col->title);
}

void TaskWindow::on_bind_description(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
     	auto col = std::dynamic_pointer_cast<TaskModel>(list_item->get_item());
      if ( !col ) return;

      auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
      if ( !label ) return;

	label->set_text(col->description);
}

void TaskWindow::on_bind_mark(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
     	auto col = std::dynamic_pointer_cast<TaskModel>(list_item->get_item());
      if ( !col ) return;

      auto box = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
      if ( !box ) return;

	box->set_active(col->mark);
}



TaskWindow::TaskWindow():
	Gtk::Box(Gtk::Orientation::VERTICAL)
{
	this->append(m_scroll_win);
 	m_scroll_win.set_child(m_column);
	m_scroll_win.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
	m_scroll_win.set_expand();

	m_list = Gio::ListStore<TaskModel>::create();

 	auto select_model =  Gtk::SingleSelection::create(m_list);
  	select_model->set_autoselect(false);
   	m_column.set_model(select_model);

 	auto factory = Gtk::SignalListItemFactory::create();
  	factory->signal_setup().connect(
   		sigc::mem_fun(*this, &TaskWindow::on_setup_mark)
   	);
   	factory->signal_bind().connect(
    		sigc::mem_fun(*this, &TaskWindow::on_bind_mark)
    	);
	      auto column = Gtk::ColumnViewColumn::create("Concluído", factory);
	      m_column.append_column(column);


		factory = Gtk::SignalListItemFactory::create();
  	factory->signal_setup().connect(
   		sigc::mem_fun(*this, &TaskWindow::on_setup_label)
   	);
   	factory->signal_bind().connect(
    		sigc::mem_fun(*this, &TaskWindow::on_bind_index)
    	);
	      column = Gtk::ColumnViewColumn::create("Index", factory);
	      m_column.append_column(column);


		factory = Gtk::SignalListItemFactory::create();
  	factory->signal_setup().connect(
   		sigc::mem_fun(*this, &TaskWindow::on_setup_label)
   	);
   	factory->signal_bind().connect(
    		sigc::mem_fun(*this, &TaskWindow::on_bind_title)
    	);
	      column = Gtk::ColumnViewColumn::create("Título", factory);
	      m_column.append_column(column);


		factory = Gtk::SignalListItemFactory::create();
  	factory->signal_setup().connect(
   		sigc::mem_fun(*this, &TaskWindow::on_setup_label)
   	);
   	factory->signal_bind().connect(
    		sigc::mem_fun(*this, &TaskWindow::on_bind_description)
    	);
	      column = Gtk::ColumnViewColumn::create("Descrição", factory);
	      m_column.append_column(column);
}

void TaskWindow::loadTask(kb::Task& tsk, kb::index i)
{
	m_list->append(
		TaskModel::create(
			i,
			tsk.getMark(),
			tsk.getTitle(),
			tsk.getDescription()
		)
	);
}

void TaskWindow::clearTasks() {
	m_list.reset();
}
