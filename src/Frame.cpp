#include "Frame.hpp"
#include <cstddef>
#include <cstdint>

bool kb::Frame::duplicated(const std::string& title) {
    for(auto& t: tasks) {
        if (t.getTitle() == title) {
            return true;
        }
    }
    return false;
}

std::pair<size_t, kb::SuperTask*> kb::Frame::newSuperTask(std::string title_, std::string description_) {
    if(duplicated(title_)) {return {SIZE_MAX, nullptr};}

    tasks.push_back({title_, description_});
    return getSuperTask(title_);
}

std::pair<size_t, kb::SuperTask*> kb::Frame::newSuperTask(kb::SuperTask& st) {
    if(duplicated(st.getTitle())) {return {SIZE_MAX, nullptr};}

    tasks.push_back(st);
    return getSuperTask(st.getTitle());
}

kb::SuperTask* kb::Frame::getSuperTask(size_t index) {
    if(index >= tasks.size()) {return nullptr;}
    return &tasks.at(index);
}

std::pair<size_t, kb::SuperTask*> kb::Frame::getSuperTask(std::string title) {
    size_t i = 0;
    for(auto& st: this->tasks) {
        if(st.getTitle() == title) {return {i, &st};}
        i++;
    }
    return {SIZE_MAX, nullptr};
}



bool kb::Frame::deleteSuperTask(size_t index, bool force) {
    auto it = tasks.begin();
    size_t i = 0;
    while(it != tasks.end()) {
        if(i == index && (force || it->Markable())) {
            tasks.erase(it);
            return true;
        }
        it++; i++;
    }
    return false;
}


bool kb::Frame::deleteSuperTask(std::string title_, bool force) {
    auto it = tasks.begin();
    while(it != tasks.end()) {
        if(it->getTitle() == title_ && (force || it->Markable())) {
            tasks.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool kb::Frame::Markable() {
    for(auto& st: tasks) {
        if(!st.Markable()) {return false;}
    }
    return true;
}
