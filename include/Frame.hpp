#include "SuperTask.hpp"
#include <cstddef>
#include <string>
#include <vector>
namespace kb
{
    class Frame {
        std::string name;
        std::vector<kb::SuperTask> tasks;

        bool duplicated(const std::string& title);
        public:
            Frame() = delete;
            Frame(std::string name_): name(name_) {}

            bool newSuperTask(std::string title_, std::string description_);
            bool newSuperTask(kb::SuperTask& st);

            bool deleteSuperTask(size_t index, bool force);
            bool deleteSuperTask(std::string title_, bool force);

            const std::string& getName() const {return name;}
            kb::SuperTask* getSuperTask(size_t index);
            kb::SuperTask* getSuperTask(std::string title);

            auto cbegin() const {return tasks.cbegin();}
            auto cend() const {return tasks.cend();}

            auto begin() {return tasks.begin();}
            auto end() {return tasks.end();}

            size_t size() const {return tasks.size();}
    };
};
