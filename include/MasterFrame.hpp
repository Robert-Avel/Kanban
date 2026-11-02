#include <cstddef>
#include <string>
#include <vector>
#include "Frame.hpp"




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
    };

    class MasterFrame {
        std::vector<kb::Frame> frames;

        static bool Markable(Frame& f);
        bool duplicated(const std::string& name);
        kb::Frame* _getFrame(size_t index);
        Status _moveTask(kb::Frame& origin_fram, kb::SuperTask& task, kb::Frame& dest_frame);

        public:
            MasterFrame() = default;

            Status newFrame(kb::Frame f);
            const kb::Frame* getFrame(size_t index) const;

            auto cbegin() const {return frames.cbegin();}
            auto cend() const {return frames.cend();}

            auto begin() {return frames.begin();}
            auto end() {return frames.end();}

            Status mvSuperTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force);

            Status newFrame(std::string name);
            Status newSuperTask(size_t frame_index, std::string title, std::string description);
            Status newSubTask(size_t frame_index, size_t super_tsk_index, std::string title, std::string description);

            Status switchMarkSuperTask(size_t frame_index, size_t super_tsk_index, bool force);
            Status switchMarkSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index);

            Status deleteFrame(size_t frame_index, bool force);
            Status deleteSuperTask(size_t frame_index, size_t super_tsk_index, bool force);
            Status deleteSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index);
    };
}
