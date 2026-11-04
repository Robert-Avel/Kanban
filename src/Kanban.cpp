#include "Kanban.hpp"
#include "Data.hpp"
#include "MasterFrame.hpp"
#include "Payload.hpp"
#include "SuperTask.hpp"
#include <ctime>
#include <string>

#define DATA_FILE_EXT ".bin"


kb::BasePayLoad kb::Kanban::Open(std::string name) {
    std::ifstream file;
    if(name.empty())
        {return {NO_INPUT, this->app_data_path + "???" + DATA_FILE_EXT, "NO_NAME"};}
    auto final_path = this->app_data_path + name + DATA_FILE_EXT;

    file.open(final_path, std::ios::in | std::ios::app | std::ios::binary);
    if(!file) {return {FAIL, final_path, "NO_NAME"};}

    auto buffer = kb::Data1::load(file, final_path);
    file.close();

    if(buffer.has_value()) {
        kanban = buffer.value();
        return {SUCCESS, this->kanban};
    }
    else {return {FAIL, final_path, "FAIL_READ"};}
}


kb::BasePayLoad kb::Kanban::Save(std::string name) {
    std::ofstream file;
    if(name.empty() && this->kb_name.empty())
        {return {NO_INPUT, this->app_data_path + "???" + DATA_FILE_EXT, "NO_NAME"};}

    auto final_path = this->app_data_path + (name.empty() ? kb_name : name) + DATA_FILE_EXT;
    file.open(final_path , std::ios::out | std::ios::binary | std::ios::trunc);

    kb::Data1::save(file, this->kanban);
    file.close();
    return {SUCCESS, this->kanban};
}


kb::BasePayLoad kb::Kanban::newTask(index frame, index super_task, const std::string& title, const std::string& description) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    auto res = st->newSubTask({title, description});
    if(res.second == nullptr) {return {DUPLICATED, title};}

    return {SUCCESS, res.first};
}


kb::BasePayLoad kb::Kanban::newSuperTask(index frame, const std::string& title, const std::string& description) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto res = f->newSuperTask(title, description);
    if(res.second == nullptr) {return {DUPLICATED, title};}

    return {SUCCESS, res.first};
}


kb::BasePayLoad kb::Kanban::newFrame(const std::string& name) {
    auto res = kanban.newFrame(name);
    if(res.second == nullptr) {return {DUPLICATED, name};}

    return {SUCCESS, res.first};
}


kb::BasePayLoad kb::Kanban::deleteTask(index frame, index super_task, index task) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    auto* t = st->getTask(task);
    if(t == nullptr) {return {TASK_NOT_FOUND, task};}

    auto tmp = t->getTitle();
    if(!st->deleteSubTask(task)) {return {FAIL, *t};}
    else return {SUCCESS, tmp};
}


kb::BasePayLoad kb::Kanban::deleteSuperTask(index frame, index super_task, bool force) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    auto tmp = st->getTitle();
    if(st->Markable() && !force) {return {INCOMPLETE_MARK, *st};}
    else if(!f->deleteSuperTask(super_task, force)) {return {FAIL, *st};}
    else return {SUCCESS, tmp};
}


kb::BasePayLoad kb::Kanban::deleteFrame(index frame, bool force) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto tmp = f->getName();
    if(f->Markable() && !force) {return {INCOMPLETE_MARK, *f};}
    else if(!kanban.deleteFrame(frame, force)) {return {FAIL, *f};}
    else return {SUCCESS, tmp};
}


kb::BasePayLoad kb::Kanban::markTask(index frame, index super_task, index task) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    auto* t = st->getTask(task);
    if(t == nullptr) {return {TASK_NOT_FOUND, task};}

    st->Mark(true);
    return {SUCCESS, *t};
}

kb::BasePayLoad kb::Kanban::markSuperTask(index frame, index super_task, bool force) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    if(st->Mark(force)) {return {INCOMPLETE_MARK, *st};}
    else return {SUCCESS, *st};
}


kb::BasePayLoad kb::Kanban::unmarkTask(index frame, index super_task, index task) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    auto* t = st->getTask(task);
    if(t == nullptr) {return {TASK_NOT_FOUND, task};}

    st->unMark();
    return {SUCCESS, *t};
}

kb::BasePayLoad kb::Kanban::unmarkSuperTask(index frame, index super_task) {
    auto* f = kanban.getFrame(frame);
    if(f == nullptr) {return {FRAME_NOT_FOUND, frame};}

    auto* st = f->getSuperTask(super_task);
    if(st == nullptr) {return {SUPER_TASK_NOT_FOUND, super_task};}

    st->unMark();
    return {SUCCESS, *st};
}


kb::BasePayLoad kb::Kanban::moveSuperTask(index origin_frame, index super_task, index dest_frame, bool force) {
    auto res = kanban.mvSuperTask(origin_frame, super_task, dest_frame, force);
    auto st_target = kanban.getFrame(origin_frame)->getSuperTask(super_task);
    switch (res.second) {
        case SUCCESS:
            return {SUCCESS, res.first};
        case SUPER_TASK_NOT_FOUND:
            return {SUPER_TASK_NOT_FOUND, res.first};
        case FRAME_NOT_FOUND:
            return {FRAME_NOT_FOUND, res.first};
        case INCOMPLETE_MARK:
            return {INCOMPLETE_MARK, *st_target};
        case DUPLICATED:
            return {DUPLICATED, *st_target};
        default:
            return {FAIL, *st_target};
    }
}
