#ifndef DATA_HPP
#define DATA_HPP


#include <ByteS.hpp>
#include <MasterFrame.hpp>
#include <fstream>
#include <optional>
#include <utility>
#include <vector>

using UpdateOverride = void (*) (kb::MasterFrame& mfrm);
using LoadOverride = std::optional<kb::MasterFrame> (*) (ByteS& d);
using OverridePair = std::pair<LoadOverride, UpdateOverride>;
//Criar classe de sobreposição de varias versões de dados


namespace kb {
	namespace Data1 {
	        ByteS appendTask(kb::Task& tsk);
	        ByteS appendSuperTask(kb::SuperTask& stsk);
	        ByteS appendFrame(kb::Frame& frm);
	        ByteS appendMasterFrame(kb::MasterFrame& mfrm);

	        std::optional<kb::Task> popTask(ByteS& d);
	        std::optional<kb::SuperTask> popSuperTask(ByteS& d);
	        std::optional<kb::Frame> popFrame(ByteS& d);
	        std::optional<kb::MasterFrame> popMasterFrame(ByteS& d);
	};


	namespace DataManager {
		static const std::vector<OverridePair> version_wrapper = {
			{nullptr, nullptr}, //versão zero (nulo)
			{Data1::popMasterFrame, nullptr} //primeira versão não possui atualização
		};

		size_t getLastVersion();
		bool save(std::ofstream& f,kb::MasterFrame& mfrm);
		std::optional<kb::MasterFrame> load(std::ifstream& f, std::string& filepath);
	};
};

#endif
