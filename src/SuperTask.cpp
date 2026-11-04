#include "SuperTask.hpp"
#include <cstdint>

bool kb::SuperTask::duplicated(const std::string& title) {
    for(auto& t: sub_tsk) {
        if (t.getTitle() == title) {
            return true;
        }
    }
    return false;
}


kb::Task* kb::SuperTask::getTask(size_t index) {
    if(index >= sub_tsk.size()) {return nullptr;}
    return &sub_tsk.at(index);
}


std::pair<size_t, kb::Task*> kb::SuperTask::getTask(std::string title) {
    size_t i = 0;
    for(auto& t: sub_tsk) {
        if (t.getTitle() == title) {
            return { i , &t };
        }
        i++;
    }
    return {SIZE_MAX, nullptr};
}


std::pair<size_t, kb::Task*> kb::SuperTask::newSubTask(kb::Task tsk) {
    auto t = this->getTask(tsk.getTitle());
    if(t.second != nullptr) {return {SIZE_MAX, nullptr};}

    sub_tsk.push_back(tsk);
    return getTask(tsk.getTitle());
}


bool kb::SuperTask::deleteSubTask(size_t index) {
    auto it = sub_tsk.cbegin();
    size_t i = 0;
    while(it != sub_tsk.cend()) {
        if(i == index) {
            sub_tsk.erase(it);
            return true;
        }
        it++; i++;
    }
    return false;
}

bool kb::SuperTask::deleteSubTask(std::string title) {
    auto it = sub_tsk.cbegin();
    while(it != sub_tsk.cend()) {
        if(title == it->getTitle()) {
            sub_tsk.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool kb::SuperTask::Markable() const {
    if(marked) {return true;}
    for(auto& t: sub_tsk) {
        if (!t.getMark()) {
            return false;
        }
    }
    return true;
}

bool kb::SuperTask::Mark(bool force) {
    if(force) {marked = true; return true;}

    if(!this->Markable()) {return false;}
    this->marked = true;
    return true;
}

bool kb::SuperTask::switchMark(bool force) {
    if(marked) {
        unMark();
        return false;
    }
    else { return Mark(force); }
}
