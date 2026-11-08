#include "SuperTask.hpp"
#include "Task.hpp"
#include "giomm/liststore.h"
#include "glibmm/object.h"
#include "gtkmm/box.h"
#include "gtkmm/columnview.h"
#include "gtkmm/listitem.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/window.h"


class TaskModel: public Glib::Object {
    	protected:
     	TaskModel(
    		uint64_t index_,
	      bool mark_,
	      const Glib::ustring& title_,
		const Glib::ustring& description_
     	):
     	index(index_), mark(mark_), title(title_), description(description_) {}

      public:
     	uint64_t index;
     	bool mark;
     	Glib::ustring title;
     	Glib::ustring description;

      static Glib::RefPtr<TaskModel> create(
           	uint64_t index_,
           	bool mark_,
           	const Glib::ustring& title_,
           	const Glib::ustring& description_
      )
      {
      return Glib::make_refptr_for_instance<TaskModel>(
           	new TaskModel(index_, mark_, title_, description_)
           	);
      }
};

class TaskWindow: public Gtk::Box {
	protected:
		Gtk::ColumnView m_column;
		Gtk::ScrolledWindow m_scroll_win;
		Glib::RefPtr<Gio::ListStore<TaskModel>> m_list;

		void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_setup_mark(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_index(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_title(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_description(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_mark(const Glib::RefPtr<Gtk::ListItem>& list_item);

	public:
      	TaskWindow();

       	void loadTask(kb::Task& tsk, kb::index i);
        	void clearTasks();
};
