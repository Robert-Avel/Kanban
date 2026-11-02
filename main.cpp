#include "MasterFrame.hpp"
#include <iostream>
#include <string>
#include <CerealShell/CerealShell.hpp>

std::string translateStatus(kb::Status s) {
    switch (s) {
    case kb::SET_OFF:
        return "Mark set to OFF";
    case kb::SET_ON:
        return "Mark set to ON";
    case kb::SUCCESS:
        return "Sucess Operation";
    case kb::FAIL:
        return "Fatal fail";
    case kb::TASK_NOT_FOUND:
        return "Sub Task not Found";
    case kb::SUPER_TASK_NOT_FOUND:
        return "Super Task not Found";
    case kb::FRAME_NOT_FOUND:
        return "Frame not Found";
    case kb::DUPLICATED:
        return "The value already exist (Duplicated)";
    case kb::INCOMPLETE_MARK:
        return "You must mark all Sub Tasks/Super Tasks";
    default:
        return "NULL";
    }
}

static kb::MasterFrame mf;

const std::string newFrame(std::string name) {
    return translateStatus(mf.newFrame(name));
}

std::string newSuperTask(size_t frame_index, std::string title, std::string description) {
    return translateStatus(mf.newSuperTask(frame_index, title, description));
}

std::string newSubTask(size_t frame_index, size_t super_tsk_index, std::string title, std::string description) {
    return translateStatus(mf.newSubTask(frame_index, super_tsk_index, title, description));
}


std::string switchMarkSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    return translateStatus(mf.switchMarkSuperTask(frame_index, super_tsk_index, force));

}
std::string switchMarkSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    return translateStatus(mf.switchMarkSubTask(frame_index, super_tsk_index, sub_tsk_index));
}

std::string mvSuperTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force) {
    return translateStatus(mf.mvSuperTask(origin_frame_index, task_index, dest_frame_index, force));

}


void printall() {

    for(auto& frames: mf) {
        std::cout << "Frame " << frames.getName() << '\n';

        for(auto& suptsk: frames) {
            std::cout << "\tSuper Task: " << (suptsk.getMark() ? "O" : "X") << " | " << suptsk.getTitle() << " | " << suptsk.getDescription() << '\n';

            for(auto& tsk: suptsk) {
                std::cout << "\t\tTask: " << (tsk.getMark() ? "O" : "X") << " | " << tsk.getTitle() << " | " << tsk.getDescription() << '\n';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


CPP_FUNCTION_NEW(newFrame, STRING, 1, (c0), CPP_ARG_ASSEMBLY_POS( 0, STRING ))
CPP_FUNCTION_NEW(newSuperTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, STRING) CPP_ARG_ASSEMBLY_POS(2, STRING))
CPP_FUNCTION_NEW(newSubTask, STRING, 4, (c0, c1, c2, c3), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, STRING) CPP_ARG_ASSEMBLY_POS(3, STRING))
CPP_FUNCTION_NEW(switchMarkSuperTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, BOOL))
CPP_FUNCTION_NEW(switchMarkSubTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, LONG))
CPP_FUNCTION_NEW(mvSuperTask, STRING, 4, (c0, c1, c2, c3), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, LONG) CPP_ARG_ASSEMBLY_POS(3, BOOL))
CPP_VOID_FUNCTION_NEW(printall, 0, ())

int main() {
    cs::CerealShell cs;

    cs.newFunction("nf", newFrame__outCShell);
    cs.newFunction("nst", newSuperTask__outCShell);
    cs.newFunction("nt", newSubTask__outCShell);
    cs.newFunction("pa", printall__outCShell);
    cs.newFunction("sst", switchMarkSuperTask__outCShell);
    cs.newFunction("st", switchMarkSubTask__outCShell);
    cs.newFunction("mct", mvSuperTask__outCShell);

    cs.initLoop();
}
