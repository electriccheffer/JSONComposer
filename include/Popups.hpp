#ifndef POPUPS_HPP
#define POPUPS_HPP
#include <filesystem> 
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
#endif 
