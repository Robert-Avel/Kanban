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

int main() {
    cs::CerealShell cs;

    cs.newFunction("task-new", KBCLInewTask__outCShell);
    cs.newFunction("super-task-new", KBCLnewSuperTask__outCShell);
    cs.newFunction("frame-new", KBCLnewFrame__outCShell);
    cs.newFunction("task-delete", KBCLdeleteTask__outCShell);
    cs.newFunction("super-task-delete", KBCLdeleteSuperTask__outCShell);
    cs.newFunction("frame-delete", KBCLdeleteFrame__outCShell);
    cs.newFunction("task-get", KBCLgetTask__outCShell);
    cs.newFunction("super-task-get", KBCLgetSuperTask__outCShell);
    cs.newFunction("frame-get", KBCLgetFrame__outCShell);
    cs.newFunction("task-mark", KBCLmarkTask__outCShell);
    cs.newFunction("super-task-mark", KBCLmarkSuperTask__outCShell);
    cs.newFunction("task-unmark", KBCLunmarkTask__outCShell);
    cs.newFunction("super-task-unmark", KBCLunmarkSuperTask__outCShell);
    cs.newFunction("super-task-move", KBCLmoveSuperTask__outCShell);

    cs.initLoop("KanBan > ");
}
