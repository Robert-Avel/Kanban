#include "MasterFrame.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <CerealShell/CerealShell.hpp>
#include <fstream>
#include <ios>
#include "Data.hpp"

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

kb::MasterFrame mf;


std::string switchMarkSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    return translateStatus(mf.switchMarkSuperTask(frame_index, super_tsk_index, force));

}
std::string switchMarkSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    return translateStatus(mf.switchMarkSubTask(frame_index, super_tsk_index, sub_tsk_index));
}

std::string mvSuperTask(size_t origin_frame_index, size_t task_index, size_t dest_frame_index, bool force) {
    return translateStatus(mf.mvSuperTask(origin_frame_index, task_index, dest_frame_index, force));
}

std::string deleteFrame(size_t frame_index, bool force) {
    return translateStatus(mf.deleteFrame(frame_index, force));
}

std::string deleteSuperTask(size_t frame_index, size_t super_tsk_index, bool force) {
    return translateStatus(mf.deleteSuperTask(frame_index, super_tsk_index, force));
}

std::string deleteSubTask(size_t frame_index, size_t super_tsk_index, size_t sub_tsk_index) {
    return translateStatus(mf.deleteSubTask(frame_index, super_tsk_index, sub_tsk_index));
}


void printall(kb::MasterFrame& mf) {
    size_t i = 0;
    for(auto& frames: mf) {
        std::cout << " <" << i << "> Frame " << frames.getName() << '\n';

        size_t ii = 0;
        for(auto& suptsk: frames) {
            std::cout << "\t<" << i << '.' << ii << "> " << (suptsk.getMark() ? "O" : "X") << " | " << suptsk.getTitle() << " | " << suptsk.getDescription() << '\n';

            size_t iii = 0;
            for(auto& tsk: suptsk) {
                std::cout << "\t\t<" << i << '.' << ii << '.' << iii << "> " << (tsk.getMark() ? "O" : "X") << " | " << tsk.getTitle() << " | " << tsk.getDescription() << '\n';
                iii++;
            }
            ii++;
        }
        i++;
    }
}
void printall() {printall(mf);}


CPP_FUNCTION_NEW(switchMarkSuperTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, BOOL))
CPP_FUNCTION_NEW(switchMarkSubTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, LONG))
CPP_FUNCTION_NEW(mvSuperTask, STRING, 4, (c0, c1, c2, c3), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, LONG) CPP_ARG_ASSEMBLY_POS(3, BOOL))
CPP_FUNCTION_NEW(deleteFrame, STRING, 2, (c0, c1), CPP_ARG_ASSEMBLY_POS( 0, LONG )  CPP_ARG_ASSEMBLY_POS(1, BOOL))
CPP_FUNCTION_NEW(deleteSuperTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS( 1, LONG )  CPP_ARG_ASSEMBLY_POS(2, BOOL))
CPP_FUNCTION_NEW(deleteSubTask, STRING, 3, (c0, c1, c2), CPP_ARG_ASSEMBLY_POS( 0, LONG ) CPP_ARG_ASSEMBLY_POS(1, LONG) CPP_ARG_ASSEMBLY_POS(2, LONG))
CPP_VOID_FUNCTION_NEW(printall, 0, ())


void lload() {
    std::string FILE_NAME = "data.bin";
    std::ifstream data(FILE_NAME, std::ios::in | std::ios::app | std::ios::binary);
    auto buffer = kb::Data1::load(data, FILE_NAME);
    if(buffer.has_value()) {mf = buffer.value();}
    else mf = {};
    data.close();
}

void save() {
    std::ofstream data;
    data.open("data.bin", std::ios::out | std::ios::binary | std::ios::trunc);
    kb::Data1::save(data, mf);
    data.close();
}


int main() {
    cs::CerealShell cs;

    cs.newFunction("pa", printall__outCShell);
    cs.newFunction("sst", switchMarkSuperTask__outCShell);
    cs.newFunction("st", switchMarkSubTask__outCShell);
    cs.newFunction("mct", mvSuperTask__outCShell);
    cs.newFunction("df", deleteFrame__outCShell);
    cs.newFunction("dst", deleteSuperTask__outCShell);
    cs.newFunction("dt", deleteSubTask__outCShell);

    lload();
    cs.initLoop();
    save();
}
