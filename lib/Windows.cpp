#include "../include/Windows.hpp"

void ObjectBrowserWindow::Render(){

	ImGui::SetNextWindowPos(this->position);
	ImGui::SetNextWindowSize(ImVec2(this->size.x * 0.5f, this->size.y ));
	ImGui::Begin("Left", nullptr, 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("Left Panel");
	ImGui::End();
}

void FileBrowserWindow::Render(){
	
	ImGui::SetNextWindowPos(ImVec2(this->size.x * 0.5f + this->position.x, this->position.y));
	ImGui::SetNextWindowSize(ImVec2(this->size.x * 0.7f, this->size.y * 0.5f));
	ImGui::Begin("Right-Top", nullptr, 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("Right Top Panel");
	ImGui::End();
}

void InputWindow::Render(){
	
	ImGui::SetNextWindowPos(ImVec2(this->position.x + this->size.x * 0.5f,
						 this->position.y + this->size.y * 0.5f));
	ImGui::SetNextWindowSize(ImVec2(this->size.x , this->size.y));
	ImGui::Begin("Right-Bottom", nullptr, 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("Right Bottom Panel");
	ImGui::End();	

}
