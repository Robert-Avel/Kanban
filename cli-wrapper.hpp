#include "Frame.hpp"
#include "Kanban.hpp"
#include "MasterFrame.hpp"
#include "Payload.hpp"
#include "SuperTask.hpp"
#include <cstdint>
#include <sstream>
#include <string>
#include <variant>

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


std::string insertTab(uint16_t level) {
	return std::string(level, '\t');
}


static std::string formatTask(const kb::Task& t, uint16_t tab_level)
{
	return insertTab(tab_level).c_str() + (t.getMark() ? MARKDED : UNMARKDED) + SEPARATOR
	+ t.getTitle() + SEPARATOR + t.getDescription() + '\n';
}

static std::string formatSuperTask(const kb::SuperTask& st, uint16_t tab_level)
{
	std::stringstream buffer;
	buffer << insertTab(tab_level) << (st.getMark() ? MARKDED : UNMARKDED) << SEPARATOR
	<< st.getTitle() << SEPARATOR << st.getDescription() << '\n';

	buffer << insertTab(tab_level) << "< TASKS >\n";
	if(st.size() == 0) {buffer << insertTab(tab_level + 1) << "[ NO TASKS ]";}
	for(const kb::Task& t: st) {
		buffer << formatTask(t, tab_level + 1);
	}
	return buffer.str();
}

static std::string formatFrame(const kb::Frame& f, uint16_t tab_level)
{
	std::stringstream buffer;
	buffer << insertTab(tab_level) << "Frame : " << f.getName() << "\n";

	buffer << insertTab(tab_level) << "< SUPER TASKS >\n";
	if(f.size() == 0) {buffer << insertTab(tab_level + 1) << "[ NO SUPER TASKS ]";}
	for(const kb::SuperTask& st: f) {
		buffer << formatSuperTask(st, tab_level + 1);
	}
	buffer << '\n';
	return buffer.str();
}

static std::string formatMasterFrame(const kb::MasterFrame& mf, uint16_t tab_level)
{
	std::stringstream buffer;

	buffer << insertTab(tab_level) << "< FRAMES >\n";
	if(mf.size() == 0) {return insertTab(tab_level + 1) + "[ NO FRAMES ]";}
	for(const kb::Frame& f: mf) {
		buffer << formatFrame(f, tab_level + 1) << '\n';
	}
	return buffer.str();
}


static std::string formatVariant(const kb::OpData& v)
{
	if (std::holds_alternative<kb::MasterFrame>(v)) {
		return formatMasterFrame(std::get<kb::MasterFrame>(v), 0);
	} else if(std::holds_alternative<kb::Frame>(v)) {
           	return formatFrame(std::get<kb::Frame>(v), 0);
      } else if(std::holds_alternative<kb::SuperTask>(v)) {
      	return formatSuperTask(std::get<kb::SuperTask>(v), 0);
      } else if(std::holds_alternative<kb::Task>(v)) {
		return formatTask(std::get<kb::Task>(v), 0);
	} else if(std::holds_alternative<std::string>(v)) {
           	return std::get<std::string>(v);
	} else if(std::holds_alternative<kb::index>(v)) {
		return std::to_string(std::get<kb::index>(v));
	} else return "NULL";
}

static std::string formatPayLoad(const kb::BasePayLoad& bp) {
	const std::string* message = bp.getMessage();
	return STATUS[bp.getStatus() + 2] + "\n"
	+ ((message == nullptr) ? "": *message) + '\n'
 	+ formatVariant(bp.getVariant());
}

std::string KBCLInewTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	const std::string& title,
	const std::string& description
)
{
	return formatPayLoad(kanban.newTask(frame, super_task, title, description));
}

std::string KBCLnewSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	const std::string& title,
	const std::string& description)
{
	return formatPayLoad(kanban.newSuperTask(frame, title, description));
}


std::string KBCLnewFrame(kb::Kanban& kanban, const std::string& name)
{
	return formatPayLoad(kanban.newFrame(name));
}


std::string KBCLdeleteTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task,
	bool force
)
{
	return formatPayLoad(kanban.deleteTask(frame, super_task, task, force));
}


std::string KBCLdeleteSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	bool force
)
{
	return formatPayLoad(kanban.deleteSuperTask(frame, super_task, force));
}


std::string KBCLdeleteFrame(kb::Kanban& kanban, kb::index frame, bool force)
{
	return formatPayLoad(kanban.deleteFrame(frame, force));
}


std::string KBCLgetTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
)
{
	return formatPayLoad(kanban.getTask(frame, super_task, task));
}

std::string KBCLgetSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task
)
{
	return formatPayLoad(kanban.getSuperTask(frame, super_task));
}

std::string KBCLgetFrame(kb::Kanban& kanban, kb::index frame)
{
	return formatPayLoad(kanban.getFrame(frame));
}

std::string KBCLgetKanban(kb::Kanban& kanban)
{
	return formatPayLoad(kanban.getKanban());
}


std::string KBCLmarkTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
)
{
	return formatPayLoad(kanban.markTask(frame, super_task, task));
}


std::string KBCLmarkSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	bool force
)
{
	return formatPayLoad(kanban.markSuperTask(frame, super_task, force));
}


std::string KBCLunmarkTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task,
	kb::index task
)
{
	return formatPayLoad(kanban.unmarkTask(frame, super_task, task));
}


std::string KBCLunmarkSuperTask(
	kb::Kanban& kanban,
	kb::index frame,
	kb::index super_task
)
{
	return formatPayLoad(kanban.unmarkSuperTask(frame, super_task));
}


std::string KBCLmoveSuperTask(
	kb::Kanban& kanban,
	kb::index origin_frame,
	kb::index super_task,
	kb::index dest_frame,
	bool force
)
{
	return formatPayLoad(kanban.moveSuperTask(origin_frame, super_task, dest_frame, force));
}


std::string KBCLOpen(kb::Kanban& kanban, std::string name)
{
	return formatPayLoad(kanban.Open(name));
}

std::string KBCLSave(kb::Kanban& kanban)
{
	return formatPayLoad(kanban.Save());
}

std::string KBCLgetKbName(kb::Kanban& kanban)
{
	return formatPayLoad(kanban.getKbName());
}

std::string KBCLsetKbName(kb::Kanban& kanban, const std::string name)
{
	return formatPayLoad(kanban.setKbName(name));

}
