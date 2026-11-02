#include "SuperTask.hpp"
#include <cstddef>
#include <string>
#include <vector>
namespace kb
{
    class Frame {
        std::string name;
        std::vector<kb::SuperTask> tasks;

        public:
            Frame() = delete;
            Frame(std::string name_): name(name_) {}

            bool newTask(std::string title_, std::string description_);
            bool deleteTask(std::string title_, std::string description_, bool force);


            const std::string& getName() const {return name;}
            const kb::SuperTask getSuperTask(size_t index) const;
            const kb::Task getSubTask(size_t super_index, size_t sub_index) const;

            bool markSuperTask(size_t index);
            bool markSubTask(size_t super_index, size_t sub_index);


            auto begin() {return tasks.cbegin();}
            auto end() {return tasks.cend();}

            size_t size() const {return tasks.size();}
    };
};
