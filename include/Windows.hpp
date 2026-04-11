#ifndef WINDOWS_HPP
#define WINDOWS_HPP
#include "../third_party/imgui/imgui.h"
#include <vector>

class ObjectBrowserWindow{
	
	protected:
		ImVec2& size; 
		ImVec2& position; 	
	public: 
		ObjectBrowserWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}
		void Render(); 
}; 

class FileBrowserWindow{
	
	protected: 
		ImVec2& size; 
		ImVec2& position; 	
	
	public: 
		FileBrowserWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}

		void Render(); 
}; 

class InputWindow{
	
	protected:
		ImVec2& size; 
		ImVec2& position;

	public:
		InputWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}
		
		void Render(); 

};

#endif
