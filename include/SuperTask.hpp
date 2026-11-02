#include "Task.hpp"
#include <cstddef>
#include <vector>

namespace kb {
    using SubTasks = std::vector<kb::Task>;

    class SuperTask: public kb::Task {
        SubTasks sub_tsk;

        public:
            SuperTask() = delete;
            SuperTask(std::string title_, std::string description_): kb::Task(title_, description_) {}
            bool newSubTask(kb::Task tsk);

            bool deleteSubTask(size_t index);
            bool deleteSubTask(std::string title);
            void deleteSubTask(SubTasks::const_iterator title);

            const Task* getTask(size_t index) const;
            const Task* getTask(std::string title) const;

            bool Markable() const;

            bool Mark(bool force);
            void unMark();
            bool switchMark(bool force);

            bool getMark() const;

            auto begin() {return sub_tsk.cbegin();}
            auto end() {return sub_tsk.cend();}

            size_t size() const {return sub_tsk.size();}
    };
};
