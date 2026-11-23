#ifndef SUPER_TASK_HPP
#define SUPER_TASK_HPP

#include "Task.hpp"
#include <cstddef>
#include <vector>



namespace kb {

    	using index = size_t;

    	using SubTasks = std::vector<kb::Task>;

     	class SuperTask: public kb::Task {
	      SubTasks sub_tsk;

		inline bool deletable(const kb::Task t, bool force)
	 		{return t.getMark() || force;}
	      bool duplicated(const std::string& title);

	      public:
	            SuperTask() = delete;
	            SuperTask(std::string title_, std::string description_):
	            kb::Task(title_, description_) {}
	            SuperTask(std::string title_, std::string description_, bool mark):
	            kb::Task(title_, description_, mark) {}

	            std::pair<index, Task*> newSubTask(kb::Task tsk);

	            bool deleteSubTask(index index, bool force);
	            bool deleteSubTask(std::string title, bool force);

	            std::pair<index, Task*> getTask(std::string title);
	            Task* getTask(index index);

	            void clear() {sub_tsk.clear();}

	            bool Markable() const override;

	            bool Mark(bool force) override;
	            bool switchMark(bool force) override;

	            auto begin() const {return sub_tsk.cbegin();}
	            auto end() const {return sub_tsk.cend();}

	            auto begin() {return sub_tsk.begin();}
	            auto end() {return sub_tsk.end();}

	            size_t size() const {return sub_tsk.size();}
    	};
};

#endif
