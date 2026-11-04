#ifndef PAYLOAD_HPP
#define PAYLOAD_HPP

#include "Frame.hpp"
#include "MasterFrame.hpp"
#include "SuperTask.hpp"
#include "Task.hpp"
#include <cstddef>
#include <string>
#include <variant>


namespace kb {

    using OpData = std::variant<MasterFrame, Frame, SuperTask, Task, std::string, index>;

    class BasePayLoad {
        Status status;
        OpData payload;
        std::string message;

        public:
            BasePayLoad() = delete;

            BasePayLoad(Status status_, const OpData& payload_):
            status(status_), payload(payload_) {}

            BasePayLoad(Status status_, const OpData& payload_, const std::string message_):
            status(status_), payload(payload_), message(message_) {}

            const MasterFrame* getMasterFrame() {return std::get_if<MasterFrame>(&payload);}
            const Frame* getFrame() {return std::get_if<Frame>(&payload);}
            const SuperTask* getSuperTask() {return std::get_if<SuperTask>(&payload);}
            const Task* getTask() {return std::get_if<Task>(&payload);}
            const std::string* getString() {return std::get_if<std::string>(&payload);}
            const index* getIndex() {return std::get_if<index>(&payload);}

            const std::string* getMessage() {return (message.empty() ? nullptr: &message);}
            const Status& getStatus() {return status;}
    };
}

#endif
