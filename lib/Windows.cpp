#include "../include/Windows.hpp"

void InputWindow::Render(){
	
	ImGui::SetNextWindowPos(ImVec2(this->position.x + this->size.x * 0.5f,
						 this->position.y + this->size.y * 0.5f));
	ImGui::SetNextWindowSize(ImVec2(this->size.x , this->size.y));
	ImGui::Begin("Right-Bottom", nullptr, 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("Right Bottom Panel");
	ImGui::End();	
	


}
