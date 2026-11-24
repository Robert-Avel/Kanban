#include "Data.hpp"
#include <ByteS.hpp>
#include <cstddef>
#include <iostream>
#include <vector>


ByteS kb::Data1::appendTask(kb::Task& tsk) {
    ByteS b;
    b.append(tsk.getTitle());
    b.append(tsk.getDescription());
    b.append(tsk.getMark());
    return b;
}


ByteS kb::Data1::appendSuperTask(kb::SuperTask& stsk) {
    ByteS b = appendTask(stsk);
    b.append(stsk.size());

    for(auto& f: stsk) {
        b << appendTask(f);
    }

    return b;
}


ByteS kb::Data1::appendFrame(kb::Frame& frm) {
    ByteS b;
    b.append(frm.getName());
    b.append(frm.size());

    for(auto& st: frm) {
        b << kb::Data1::appendSuperTask(st);
    }
    return b;
}


ByteS kb::Data1::appendMasterFrame(kb::MasterFrame& mfrm) {
    ByteS b;
    b.append(mfrm.size());

    for(auto& fr: mfrm) {
        b << kb::Data1::appendFrame(fr);
    }
    return b;
}


std::optional<kb::Task> kb::Data1::popTask(ByteS& d) {
    std::string title;
    std::string description;
    bool mark = {};

    d.pop(title);
    d.pop(description);
    d.pop<bool>(mark);

    return kb::Task{title, description, mark};
}


std::optional<kb::SuperTask> kb::Data1::popSuperTask(ByteS& d) {
    auto mst = popTask(d);
    if(!mst.has_value()) {return {};}

    kb::SuperTask output = {mst->getTitle(), mst->getDescription(), mst->getMark()};
    size_t size = {};
    d.pop(size);

    if(size == 0) {return output;}
    for(size_t i = 0; i < size; i++) {
        auto r = popTask(d);
        if(r.has_value()) {output.newSubTask(r.value());}
    }

    return output;
}


std::optional<kb::Frame> kb::Data1::popFrame(ByteS& d) {
    std::string name;
    if(!d.pop(name)) {std::cout << ""; return {};}

    kb::Frame output{name};

    size_t size = {};
    d.pop(size);
    if(size == 0) {return output;}

    for(size_t i = 0; i < size; i++) {
        auto tmp = kb::Data1::popSuperTask(d);
        if(tmp.has_value()) {output.newSuperTask(tmp.value());}
    }
    return output;
}


std::optional<kb::MasterFrame> kb::Data1::popMasterFrame(ByteS& d) {
    kb::MasterFrame output{};

    size_t size = {0};
    d.pop(size);
    if(size == 0) {return output;}

    for(size_t i = 0; i < size; i++) {
        auto tmp = kb::Data1::popFrame(d);
        if(tmp.has_value()) {output.newFrame(tmp.value());}
    }
    return output;
}


size_t kb::DataManager::getLastVersion() {return kb::DataManager::version_wrapper.size() - 1;}


bool kb::DataManager::save(std::ofstream& f, kb::MasterFrame& mfrm) {
	if(!f) {return false;}

	size_t last_version = kb::DataManager::getLastVersion();
	f.write((char*) &last_version, sizeof(size_t));
	std::cout << "Last: " << last_version << '\n';

	auto d = kb::Data1::appendMasterFrame(mfrm);
	auto dsize = d.size();
	std::cout << dsize << '\n';
	f.write((char*) &dsize, sizeof(dsize));
	f.write((char*) d.data(), d.size());
	return true;
}

std::optional<kb::MasterFrame> kb::DataManager::load(std::ifstream& f, std::string& filepath) {
	if(!f) {return {};}

	size_t version = {0};
	f.read((char*) &version, sizeof(size_t));

	size_t s = {0};
	f.read((char*) &s, sizeof(s));
	std::cout << s << '\n';

	ByteS d;
	d.resize(s);
	f.read((char*) d.data(), s);

	if(version > version_wrapper.size()) {return {};}
	LoadOverride loader = version_wrapper[version].first;
	if (loader == nullptr) {return {};}

	return kb::Data1::popMasterFrame(d);
}
