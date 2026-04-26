#ifndef POPUPS_HPP
#define POPUPS_HPP
#include <filesystem> 
#include <unordered_map>
#include <vector>
#include "../include/ViewModels.hpp"
#include "../third_party/imgui/imgui.h"

class RenameDirectoryPopup{

	public:
		RenameDirectoryPopup(std::filesystem::directory_entry& directoryEntry);
		void Render(); 
	protected:
		std::filesystem::directory_entry& entry;	
		FileViewModel fileViewModel; 		  
}; 

class RenameFilePopup{
	
	public:
		RenameFilePopup(std::filesystem::directory_entry& directoryEntry); 
		void Render(); 
	protected: 	
		std::filesystem::directory_entry& entry; 
		FileViewModel fileViewModel;
};

class NewDirectoryPopup{

	public:
		NewDirectoryPopup(std::filesystem::directory_entry& directoryEntry);
		void Render(); 
	protected: 
		std::filesystem::directory_entry& entry; 
		FileViewModel fileViewModel; 
};


class NewFilePopup{

	public: 
		NewFilePopup(std::filesystem::directory_entry& directoryEntry); 
		void Render(); 
	
	protected: 
		std::filesystem::directory_entry& entry; 
		FileViewModel fileViewModel; 
};  


class MoveDirectoryPopup{

	public: 
		MoveDirectoryPopup(std::unordered_map
				<std::string,
				std::vector<std::filesystem::directory_entry>>& directoryMap,
				std::filesystem::path& projectRoot,
				std::filesystem::path& sourceDirectory);
		void Render(); 
		
	protected:
 		void RenderHelper(std::filesystem::path filePath); 
 		std::unordered_map
			<std::string,
				std::vector<std::filesystem::directory_entry>>& directoryMap; 
		
		std::filesystem::path& projectRoot; 
		std::filesystem::path&  sourceDirectory;
		std::string  destination; 
		 
}; 						
#endif 
