#include "Kanban.hpp"
#include "SuperTask.hpp"
#include <string>

static std::string MARKDED = "[X]";
static std::string UNMARKDED = "[ ]";
static std::string SEPARATOR = " | ";

static std::string STATUS[] = {
	"Desmarcado",
      "Marcado",
      "Sucesso",
      "Falha",
      "Tarefa não encontrada",
      "Super Tarefa não encontrada",
      "Quadro não encontrado",
      "Duplicado",
      "Sub Tarefas incompletas",
      "Sem entrada"
};

std::string KBCLInewTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	const std::string& title,
	const std::string& description
);

std::string KBCLnewSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	const std::string& title,
	const std::string& description);


std::string KBCLnewFrame(kb::Kanban& kanban, const std::string& name);


std::string KBCLdeleteTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task,
	bool force
);


std::string KBCLdeleteSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	bool force
);


std::string KBCLdeleteFrame(kb::Kanban& kanban, kb::index frame, bool force);


std::string KBCLgetTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
);

std::string KBCLgetSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task
);

std::string KBCLgetFrame(kb::Kanban& kanban, kb::index frame);

std::string KBCLgetKanban(kb::Kanban& kanban);


std::string KBCLmarkTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
);

std::string KBCLmarkSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	bool force
);


std::string KBCLunmarkTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
);


std::string KBCLunmarkSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task
);


std::string KBCLmoveSuperTask(
	kb::Kanban& kanban,
	kb::index origin_frame,
	kb::index super_task,
	kb::index dest_frame,
	bool force
);


std::string KBCLOpen(kb::Kanban& kanban, std::string name);

std::string KBCLSave(kb::Kanban& kanban);

std::string KBCLgetKbName(kb::Kanban& kanban);

std::string KBCLsetKbName(kb::Kanban& kanban, const std::string name);
