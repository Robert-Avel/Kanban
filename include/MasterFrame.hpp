#ifndef MASTER_FRAME_HPP
#define MASTER_FRAME_HPP

#include <cstddef>
#include <string>
#include <vector>
#include "Frame.hpp"
#include "SuperTask.hpp"


namespace kb {
    enum Status {
        SET_OFF = -2,
        SET_ON,
        SUCCESS,
        FAIL,
        TASK_NOT_FOUND,
        SUPER_TASK_NOT_FOUND,
        FRAME_NOT_FOUND,
        DUPLICATED,
        INCOMPLETE_MARK,
        NO_INPUT,
        EMPTY
    };

    class MasterFrame {
        std::vector<kb::Frame> frames;

        static bool Markable(Frame& f);
        bool duplicated(const std::string& name);

      std::pair<kb::index, kb::Status> moveTask(kb::Frame& origin_fram, kb::SuperTask& task, kb::Frame& dest_frame);
        public:
            MasterFrame() = default;

            kb::Frame* getFrame(index index);
            std::pair<index, Frame*> getFrame(const std::string& name);

            size_t size() const {return frames.size();}

            auto begin() const {return frames.cbegin();}
            auto end() const {return frames.cend();}

            auto begin() {return frames.begin();}
            auto end() {return frames.end();}

            std::pair<kb::index, kb::Status> mvSuperTask(index origin_frame_index, index task_index, index dest_frame_index, bool force);

            std::pair<index, Frame*> newFrame(kb::Frame f);
            std::pair<index, Frame*> newFrame(std::string name);


            Status deleteFrame(index frame_index, bool force);
            void clear() {frames.clear();}
    	};
}

#endif
