#include "MasterFrame.hpp"
#include "Payload.hpp"
#include <string>

namespace kb
{
    class Kanban {
        kb::MasterFrame kanban;
        std::string app_data_path;
        std::string kb_name;

        public:
            Kanban(std::string appdata_path): app_data_path(appdata_path) {}

            BasePayLoad Open(std::string name);
            BasePayLoad Save(std::string name = "");

            BasePayLoad newTask(index frame, index super_task, const std::string& title, const std::string& description);
            BasePayLoad newSuperTask(index frame, const std::string& title, const std::string& description);
            BasePayLoad newFrame(const std::string& name);

            BasePayLoad deleteTask(index frame, index super_task, index task);
            BasePayLoad deleteSuperTask(index frame, index super_task, bool force);
            BasePayLoad deleteFrame(index frame, bool force);

            BasePayLoad markTask(index frame, index super_task, index task);
            BasePayLoad markSuperTask(index frame, index super_task, bool force);

            BasePayLoad unmarkTask(index frame, index super_task, index task);
            BasePayLoad unmarkSuperTask(index frame, index super_task);

            BasePayLoad moveSuperTask(index origin_frame, index super_task, index dest_frame, bool force);
    };
};
