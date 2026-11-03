#ifndef DATA_HPP
#define DATA_HPP


#include <ByteS.hpp>
#include <MasterFrame.hpp>
#include <optional>

namespace kb {
    class Data: public ByteS {
        public:
        Data() = default;
            void appendTask(kb::Task& tsk);
            void appendSuperTask(kb::SuperTask& stsk);
            void appendFrame(kb::Frame& frm);
            void appendMasterFrame(kb::MasterFrame& mfrm);

            std::optional<kb::Task> popTask();
            std::optional<kb::SuperTask> popSuperTask();
            std::optional<kb::Frame> popFrame();
            std::optional<kb::MasterFrame> popMasterFrame();
    };
};

#endif
