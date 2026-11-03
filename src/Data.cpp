#include "Data.hpp"
#include <cstddef>

void kb::Data::appendTask(kb::Task& tsk) {
    this->append(tsk.getTitle())
        .append(tsk.getDescription())
        .append<bool>(tsk.getMark());
}


void kb::Data::appendSuperTask(kb::SuperTask& stsk) {
    this->append(stsk.getTitle())
        .append(stsk.getDescription())
        .append<bool>(stsk.getMark())
        .append<size_t>(stsk.size());
    for(auto& t: stsk) {
        this->appendTask(t);
    }
}


void kb::Data::appendFrame(kb::Frame& frm) {
    this->append(frm.getName())
        .append<size_t>(frm.size());
    for(auto& st: frm) {
        this->appendSuperTask(st);
    }
}


void kb::Data::appendMasterFrame(kb::MasterFrame& mfrm) {
    this->append<size_t>(mfrm.size());
    for(auto& f: mfrm) {
        this->appendFrame(f);
    }
}


std::optional<kb::Task> kb::Data::popTask() {
    std::string title;
    std::string desc;
    bool mark;

    if(
        pop(title) &&
        pop(desc) &&
        pop<bool>(mark)
        ) {return kb::Task{title, desc, mark};}

    return {};
}


std::optional<kb::SuperTask> kb::Data::popSuperTask() {
    std::string title;
    std::string description;
    bool mark = {};

    if(
        !pop(title) &&
        !pop(description) &&
        !pop<bool>(mark)
        ) {return {};}

    kb::SuperTask output = {title, description, mark};

    size_t size = {};
    pop<size_t>(size);

    for(size_t i = 0; i < size; i++) {
        auto tmp = popTask();
        if(!tmp.has_value()) {return output;}
        output.newSubTask(tmp.value());
    }
    return output;
}


std::optional<kb::Frame> kb::Data::popFrame() {
    std::string name;
    if(!pop(name)) {return {};}

    kb::Frame output{name};

    size_t size = {};
    pop<size_t>(size);

    for(size_t i = 0; i < size; i++) {
        auto tmp = popSuperTask();
        if(!tmp.has_value()) {return output;}
        output.newSuperTask(tmp.value());
    }
    return output;
}


std::optional<kb::MasterFrame> kb::Data::popMasterFrame() {
    kb::MasterFrame output{};

    size_t size = {};
    pop<size_t>(size);

    for(size_t i = 0; i < size; i++) {
        auto tmp = popFrame();
        if(!tmp.has_value()) {return output;}
        output.newFrame(tmp.value());
    }
    return output;
}
