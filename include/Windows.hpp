#ifndef WINDOWS_HPP
#define WINDOWS_HPP
#include "../third_party/imgui/imgui.h"

class InputWindow{
	
	protected:
		ImVec2 size; 
		ImVec2 position; 	

	public:
		InputWindow(ImVec2& size,ImVec2& position):
						size(size),position(position){}
		
		void Render(); 

};

#endif
