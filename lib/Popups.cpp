#include "../include/Popups.hpp"

RenameDirectoryPopup::RenameDirectoryPopup(std::filesystem::directory_entry& directoryEntry):
			entry(directoryEntry){}

void RenameDirectoryPopup::Render(){
	
	if(ImGui::BeginPopup("Rename Directory")){
		
		static char buffer[256]; 
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

RenameFilePopup::RenameFilePopup(std::filesystem::directory_entry& directoryEntry)
		:entry(directoryEntry){}

void RenameFilePopup::Render(){

	if(ImGui::BeginPopup("Rename File")){
		
		static char buffer[256]; 
		ImGui::Text("New File Name: ");
		ImGui::SameLine(); 
		bool textInput = ImGui::InputText("##NewName", 
			buffer, 
			sizeof(buffer)); 
		ImGui::SameLine(); 
		bool textEntered = ImGui::Button("Ok");
		ImGui::SameLine(); 
		bool canceled = ImGui::Button("Cancel");
		if(textEntered)
		{	
			std::filesystem::path currentName = this->entry.path(); 
			std::string newFileName(buffer);
			this->fileViewModel.RenameFile(currentName,newFileName); 
			ImGui::CloseCurrentPopup();	
		}
		if(canceled){
			ImGui::CloseCurrentPopup();	
		}	
		ImGui::EndPopup();
	}

}


NewDirectoryPopup::NewDirectoryPopup(std::filesystem::directory_entry& directoryEntry)
		  :entry(directoryEntry){}
	
void NewDirectoryPopup::Render(){

	if(ImGui::BeginPopup("New Dir")){
		ImGui::Text("New Directory Name: ");
		ImGui::SameLine(); 
		
		static char buffer[256]; 
		bool textInput = ImGui::InputText("##NewName", 
				buffer, 
				sizeof(buffer)); 
		ImGui::SameLine(); 
		bool textEntered = ImGui::Button("Ok");
		ImGui::SameLine(); 
		bool canceled = ImGui::Button("Cancel");
		if(textEntered){
			std::filesystem::path entryPath = this->entry.path(); 	
			std::string newDirectoryName(buffer);
			this->fileViewModel.CreateDirectory(entryPath,
							   newDirectoryName);
			ImGui::CloseCurrentPopup();	
		}
		if(canceled){
			ImGui::CloseCurrentPopup();	
		}	
		ImGui::EndPopup();
	} 
}
	

NewFilePopup::NewFilePopup(std::filesystem::directory_entry& directoryEntry)
	     :entry(directoryEntry){}

void NewFilePopup::Render(){

	if(ImGui::BeginPopup("New File")){

		ImGui::Text("New File Name: ");
		ImGui::SameLine(); 
		static char buffer[256]; 	
		bool textInput = ImGui::InputText("##NewFile", 
			buffer, 
			sizeof(buffer)); 
		ImGui::SameLine(); 
		bool textEntered = ImGui::Button("Ok");
		ImGui::SameLine(); 
		bool canceled = ImGui::Button("Cancel");
		if(textEntered){
			
			std::filesystem::path entryPath = entry.path(); 
			std::string newFileName(buffer); 
			this->fileViewModel.NewFile(entryPath,
						    newFileName);
			ImGui::CloseCurrentPopup();	
		}
		if(canceled){
			ImGui::CloseCurrentPopup();	
		}	
		ImGui::EndPopup();
	}
} 
