#include "MasterFrame.hpp"
#include <cstddef>


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


kb::Status kb::MasterFrame::_moveTask(kb::Frame& origin_fram, kb::SuperTask& task, kb::Frame& dest_frame) {
    if(!dest_frame.newSuperTask(task)) {return DUPLICATED;}
    if(!origin_fram.deleteSuperTask(task.getTitle(), true)) {return FAIL;}

    auto* _task = dest_frame.getSuperTask(task.getTitle());
    _task->unMark();
    for(auto& t: *_task) {
        t.unMark();
    }
    return SUCCESS;
}


kb::Status kb::MasterFrame::newFrame(kb::Frame f) {
    if(duplicated(f.getName())) {return DUPLICATED;}

    frames.push_back(f);
    return SUCCESS;
}


const kb::Frame* kb::MasterFrame::getFrame(size_t index) const {
    if(index >= frames.size()) {return nullptr;}
    return &frames.at(index);}


kb::Frame* kb::MasterFrame::_getFrame(size_t index) {
    return const_cast<kb::Frame*>(getFrame(index));
}


kb::Status kb::MasterFrame::mvSuperTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force) {
    auto ori_fr = _getFrame(origin_frame_index);
    auto dest_fr = _getFrame(dest_frame_index);
    if(ori_fr == nullptr || dest_fr == nullptr) {return FRAME_NOT_FOUND;}

    auto task = ori_fr->getSuperTask(task_index);
    if(task == nullptr) {return TASK_NOT_FOUND;}
    if(!task->Markable() && force) {return INCOMPLETE_MARK;}

    return _moveTask(*ori_fr, *task, *dest_fr);
}

kb::Status kb::MasterFrame::newFrame(std::string name) {
    if(duplicated(name)) {return DUPLICATED;}
    frames.push_back({name});
    return SUCCESS;
}

kb::Status kb::MasterFrame::newSuperTask(size_t frame_index, std::string title, std::string description) {
    auto fr = _getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    if(fr->newSuperTask(title, description)) {return SUCCESS;}
    else {return DUPLICATED;}
}

kb::Status kb::MasterFrame::newSubTask(size_t frame_index, size_t super_tsk_index, std::string title, std::string description) {
    auto fr = _getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return st->newSubTask({title, description}) ? SUCCESS : DUPLICATED;
}

kb::Status kb::MasterFrame::switchMarkSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    auto fr = _getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    if(!st->Markable() && !force) {return INCOMPLETE_MARK;}
    return st->switchMark(force) ? SET_ON : SET_OFF;
}

kb::Status kb::MasterFrame::switchMarkSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    auto fr = _getFrame(frame_index);
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
    auto fr = _getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return fr->deleteSuperTask(super_tsk_index, force) ? SUCCESS : INCOMPLETE_MARK;
}


kb::Status kb::MasterFrame::deleteSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    auto fr = _getFrame(frame_index);
    if(fr == nullptr) {return FRAME_NOT_FOUND;}

    auto st = fr->getSuperTask(super_tsk_index);
    if(st == nullptr) {return SUPER_TASK_NOT_FOUND;}

    return st->deleteSubTask(super_tsk_index) ? SUCCESS : TASK_NOT_FOUND;
}
