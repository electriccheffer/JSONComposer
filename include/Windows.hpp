#ifndef WINDOWS_HPP
#define WINDOWS_HPP
#include "../third_party/imgui/imgui.h"
#include <vector>
#include <filesystem> 
#include "../include/ViewModels.hpp"

class ObjectBrowserWindow{
	
 	
	public: 
		ObjectBrowserWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){} 
		void Render(); 
	
	protected:
		ImVec2& size; 
		ImVec2& position;
		 
}; 

class FileBrowserWindow{
	

	public: 
		FileBrowserWindow(ImVec2& size,ImVec2& position,FileViewModel& fileViewModel):
				size(size),position(position),fileViewModel(fileViewModel){}

		void Render(); 

	protected: 
		void RenderFilesAndDirectories();
		void RenderFilesAndDirectories(std::filesystem::directory_entry& entry,
						std::unordered_map
						<std::string,
					std::vector<std::filesystem::directory_entry>>& map);
		ImVec2& size; 
		ImVec2& position; 
		FileViewModel& fileViewModel; 	
}; 


class InputWindow{
	
	public:
		InputWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}
		
		void Render(); 

	protected:
		ImVec2& size; 
		ImVec2& position;
};

#endif
