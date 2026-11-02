#include <cstddef>
#include <vector>
#include "Frame.hpp"


class MasterFrames {
    std::vector<kb::Frame> frames;

    bool _moveTask(kb::Frame& origin_fram, kb::SuperTask& task, kb::Frame& dest_frame);
    public:
        MasterFrames() = default;

        bool newFrame(kb::Frame f);
        const kb::Frame* getFrame(size_t index) const;

        bool moveTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force);
};
