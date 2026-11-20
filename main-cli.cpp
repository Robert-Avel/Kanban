#include "MasterFrame.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <CerealShell/CerealShell.hpp>
#include <fstream>
#include <ios>
#include "Data.hpp"
#include "cli-wrapper.hpp"

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

static kb::Kanban kaba("./");

CPP_FUNCTION_NEW(KBCLInewTask, STRING, 4, (kaba, cframe, cstask, ctitle, cdescription),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(title, STRING)
	CPP_ARG_ASSEMBLY_NAMED(description, STRING)
)


CPP_FUNCTION_NEW(KBCLnewSuperTask, STRING, 3, (kaba, cframe, ctitle, cdescription),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(title, STRING)
	CPP_ARG_ASSEMBLY_NAMED(description, STRING)
)

CPP_FUNCTION_NEW(KBCLnewFrame, STRING, 1, (kaba, cname),
	CPP_ARG_ASSEMBLY_NAMED(name, STRING)
)


CPP_FUNCTION_NEW(KBCLdeleteTask, STRING, 3, (kaba, cframe, cstask, ctask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(task, UNSIGNED_LONG)
)

CPP_FUNCTION_NEW(KBCLdeleteSuperTask, STRING, 2, (kaba, cframe, cstask, cforce),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_FLAG(force)
)

CPP_FUNCTION_NEW(KBCLdeleteFrame, STRING, 1, (kaba, cframe, cforce),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_FLAG(force)
)

CPP_FUNCTION_NEW(KBCLgetTask, STRING, 3, (kaba, cframe, cstask, ctask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(task, UNSIGNED_LONG)
)

CPP_FUNCTION_NEW(KBCLgetSuperTask, STRING, 2, (kaba, cframe, cstask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
)

CPP_FUNCTION_NEW(KBCLgetFrame, STRING, 1, (kaba, cframe),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
)

CPP_FUNCTION_NEW(KBCLgetKanban, STRING, 0, (kaba))


CPP_FUNCTION_NEW(KBCLmarkTask, STRING, 3, (kaba, cframe, cstask, ctask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(task, UNSIGNED_LONG)
)


CPP_FUNCTION_NEW(KBCLmarkSuperTask, STRING, 2, (kaba, cframe, cstask, cforce),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_FLAG(force)
)


CPP_FUNCTION_NEW(KBCLunmarkTask, STRING, 3, (kaba, cframe, cstask, ctask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(task, UNSIGNED_LONG)
)

CPP_FUNCTION_NEW(KBCLunmarkSuperTask, STRING, 2, (kaba, cframe, cstask),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
)


CPP_FUNCTION_NEW(KBCLmoveSuperTask, STRING, 3, (kaba, cframe, cstask, cmto, cforce),
	CPP_ARG_ASSEMBLY_NAMED(frame, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(stask, UNSIGNED_LONG)
	CPP_ARG_ASSEMBLY_NAMED(mto, UNSIGNED_LONG)
	CPP_ARG_FLAG(force)
)


CPP_FUNCTION_NEW(KBCLOpen, STRING, 1, (kaba, cname),
	CPP_ARG_ASSEMBLY_NAMED(name, STRING)
)


CPP_FUNCTION_NEW(KBCLSave, STRING, 0, (kaba))


CPP_FUNCTION_NEW(KBCLgetKbName, STRING, 0, (kaba))


CPP_FUNCTION_NEW(KBCLsetKbName, STRING, 1, (kaba, cname),
	CPP_ARG_ASSEMBLY_NAMED(name, STRING)
)


int main() {
    cs::CerealShell cs;

    cs.newFunction("tasknew", KBCLInewTask__outCShell);
    cs.newFunction("stasknew", KBCLnewSuperTask__outCShell);
    cs.newFunction("framenew", KBCLnewFrame__outCShell);
    cs.newFunction("taskdelete", KBCLdeleteTask__outCShell);
    cs.newFunction("staskdel", KBCLdeleteSuperTask__outCShell);
    cs.newFunction("framedel", KBCLdeleteFrame__outCShell);
    cs.newFunction("taskget", KBCLgetTask__outCShell);
    cs.newFunction("staskget", KBCLgetSuperTask__outCShell);
    cs.newFunction("frameget", KBCLgetFrame__outCShell);
    cs.newFunction("kanbanget", KBCLgetKanban__outCShell);
    cs.newFunction("taskmark", KBCLmarkTask__outCShell);
    cs.newFunction("staskmark", KBCLmarkSuperTask__outCShell);
    cs.newFunction("taskunmark", KBCLunmarkTask__outCShell);
    cs.newFunction("staskunmark", KBCLunmarkSuperTask__outCShell);
    cs.newFunction("staskmove", KBCLmoveSuperTask__outCShell);
    cs.newFunction("kanbanopen", KBCLOpen__outCShell);
    cs.newFunction("kanbansave", KBCLSave__outCShell);
    cs.newFunction("kanbangetname", KBCLgetKbName__outCShell);
    cs.newFunction("kanbansetname", KBCLsetKbName__outCShell);

    cs.initLoop("KanBan > ");
}
