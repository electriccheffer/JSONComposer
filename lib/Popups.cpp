#include "../include/Popups.hpp"

RenameDirectoryPopup::RenameDirectoryPopup(std::filesystem::directory_entry& directoryEntry):
			entry(directoryEntry){}

void RenameDirectoryPopup::Render(){
	
	static char buffer[256]; 
	if(ImGui::BeginPopup("Rename Directory")){
		ImGui::Text("New Directory Name: ");
		ImGui::SameLine(); 
		bool textInput = ImGui::InputText("##NewName", 
				buffer, 
				sizeof(buffer)); 
		ImGui::SameLine(); 
		bool textEntered = ImGui::Button("Ok");
		ImGui::SameLine(); 
		bool canceled = ImGui::Button("Cancel");
		if(textEntered){
			std::filesystem::path currentDirectory = this->entry.path(); 
			std::string newDirectoryName(buffer); 
			this->fileViewModel.RenameDirectory(currentDirectory,
							  newDirectoryName);
			ImGui::CloseCurrentPopup();	
		}
		if(canceled){
			ImGui::CloseCurrentPopup();	
		}	
		ImGui::EndPopup();
	}
}
