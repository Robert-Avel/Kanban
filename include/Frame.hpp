#ifndef FRAME_HPP
#define FRAME_HPP

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

            std::pair<index, kb::SuperTask*> newSuperTask(std::string title_, std::string description_);
            std::pair<index, kb::SuperTask*> newSuperTask(kb::SuperTask& st);

            bool deleteSuperTask(index index, bool force);
            bool deleteSuperTask(std::string title_, bool force);

            const std::string& getName() const {return name;}
            std::pair<index, kb::SuperTask*>  getSuperTask(std::string title);
            kb::SuperTask* getSuperTask(index index);

            auto cbegin() const {return tasks.cbegin();}
            auto cend() const {return tasks.cend();}

            auto begin() {return tasks.begin();}
            auto end() {return tasks.end();}

            bool Markable();
            size_t size() const {return tasks.size();}
    };
};

#endif
