#ifndef DATA_HPP
#define DATA_HPP


#include <ByteS.hpp>
#include <MasterFrame.hpp>
#include <fstream>
#include <optional>

namespace kb {
    namespace Data1 {
        ByteS appendTask(kb::Task& tsk);
        ByteS appendSuperTask(kb::SuperTask& stsk);
        ByteS appendFrame(kb::Frame& frm);
        ByteS appendMasterFrame(kb::MasterFrame& mfrm);

        std::optional<kb::Task> popTask(ByteS& d);
        std::optional<kb::SuperTask> popSuperTask(ByteS& d);
        std::optional<kb::Frame> popFrame(ByteS& d);
        std::optional<kb::MasterFrame> popMasterFrame(ByteS& d);

        bool save(std::ofstream& f,kb::MasterFrame& mfrm);
        std::optional<kb::MasterFrame> load(std::ifstream& f, std::string& filepath);
    };
};

#endif
