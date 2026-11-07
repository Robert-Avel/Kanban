#include "MasterFrame.hpp"
#include <cstddef>
#include <cstdint>


bool kb::MasterFrame::Markable(Frame& f) {
    for(auto& st: f) {
        if(!st.getMark()) {return false;}
    }
    return true;
}


bool kb::MasterFrame::duplicated(const std::string& name) {
    for (auto& fr : frames) {
        if(fr.getName() == name) {return true;}
    }
    return false;
}


std::pair<kb::index, kb::Status> kb::MasterFrame::moveTask(kb::Frame& origin_fram, kb::SuperTask& task, kb::Frame& dest_frame) {
    auto _task = dest_frame.newSuperTask(task);
    if(_task.second == nullptr) {return {SIZE_MAX, DUPLICATED};}

    if(!origin_fram.deleteSuperTask(task.getTitle(), true)) {return {SIZE_MAX, FAIL};}

    _task.second->unMark();
    for(auto& t: *_task.second) {
        t.unMark();
    }
    return {_task.first, SUCCESS};
}



kb::Frame* kb::MasterFrame::getFrame(size_t index) {
    if(index >= frames.size()) {return nullptr;}
    return &frames.at(index);}



std::pair<size_t, kb::Frame*> kb::MasterFrame::getFrame(const std::string& name) {
    size_t i = 0;
    for(auto& f: frames) {
        if(f.getName() == name) {return {i, &f};}
        i++;
    }
    return {SIZE_MAX, nullptr};
}


std::pair<size_t, kb::Frame*> kb::MasterFrame::newFrame(kb::Frame f) {
    if(duplicated(f.getName())) {return {SIZE_MAX, nullptr};}

    frames.push_back(f);
    return getFrame(f.getName());
}


std::pair<kb::index, kb::Status> kb::MasterFrame::mvSuperTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force) {
    auto ori_fr = getFrame(origin_frame_index);
    auto dest_fr = getFrame(dest_frame_index);
    if(ori_fr == nullptr) {return {origin_frame_index, FRAME_NOT_FOUND};}
    if(dest_fr == nullptr) {return {dest_frame_index, FRAME_NOT_FOUND};}

    auto task = ori_fr->getSuperTask(task_index);
    if(task == nullptr) {return {task_index, TASK_NOT_FOUND};}
    if(!task->Markable() && !force) {return {SIZE_MAX, INCOMPLETE_MARK};}

    return moveTask(*ori_fr, *task, *dest_fr);
}

std::pair<size_t, kb::Frame*> kb::MasterFrame::newFrame(std::string name) {
    if(duplicated(name)) {return {SIZE_MAX, nullptr};}
    frames.push_back({name});
    return getFrame(name);
}

kb::Status kb::MasterFrame::switchMarkSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    auto fr = getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    if(!st->Markable() && !force) {return INCOMPLETE_MARK;}
    return st->switchMark(force) ? SET_ON : SET_OFF;
}

kb::Status kb::MasterFrame::switchMarkSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    auto fr = getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    auto sbt = st->getTask(sub_tsk_index);
    if(sbt == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return sbt->switchMark(true) ? SET_ON : SET_OFF;
}

kb::Status kb::MasterFrame::deleteFrame(size_t frame_index, bool force) {
    auto it = frames.begin();
    size_t i = 0;
    while(it != frames.end()) {
        if(i == frame_index && (Markable(*it) || force)) {
            frames.erase(it);
            return SUCCESS;
        }
        it++; i++;
    }
    return FRAME_NOT_FOUND;
}

kb::Status kb::MasterFrame::deleteSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    auto fr = getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return fr->deleteSuperTask(super_tsk_index, force) ? SUCCESS : INCOMPLETE_MARK;
}


kb::Status kb::MasterFrame::deleteSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    auto fr = getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return st->deleteSubTask(super_tsk_index) ? SUCCESS : TASK_NOT_FOUND;
}
