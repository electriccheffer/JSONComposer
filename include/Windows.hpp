#ifndef WINDOWS_HPP
#define WINDOWS_HPP
#include "../third_party/imgui/imgui.h"
#include <vector>
#include <filesystem> 

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
		FileBrowserWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}

		void Render(); 

	protected: 
		void RenderFilesAndDirectories(
				std::vector<std::filesystem::directory_entry>& directoryDataList);
		ImVec2& size; 
		ImVec2& position; 	
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
