#include <unordered_map>
#include <queue>
#include "../include/Windows.hpp"
#include "../include/IO.hpp"
#include "../include/ViewModels.hpp"
#include <string> 

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
	std::filesystem::path projectRoot = this->fileViewModel.GetProjectRoot(); 
	std::string rootPathString = "Project Root: " + projectRoot.string();
	ImGui::Text("%s" ,rootPathString.c_str());
	ImGui::SameLine(); 
	ImGui::Button("Change Project Root"); 	
	ImGui::Text("-FILE EXPLORER-");
	this->RenderFilesAndDirectories();		
	ImGui::End();
}

void FileBrowserWindow::RenderFilesAndDirectories(){
	
	std::filesystem::path projectRoot = this->fileViewModel.GetProjectRoot();
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> map = 
						this->fileViewModel.ReadDirectory(projectRoot);
	
	std::vector<std::filesystem::directory_entry> rootList = map[projectRoot.string()];	
	
	for(std::filesystem::directory_entry entry : rootList){
		ImGui::PushID(entry.path().string().c_str());
		if(entry.is_directory()){
			bool isOpen = ImGui::TreeNode(entry.path().string().c_str());
			ImGui::SameLine(); 
			if(ImGui::Button("Rename")){
				
				ImGui::OpenPopup("Rename Directory");
			}
				
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
					
					ImGui::CloseCurrentPopup();	
				}
				if(canceled){
					ImGui::CloseCurrentPopup();	
				}	
				ImGui::EndPopup();
			}		
			ImGui::SameLine();
			if(ImGui::Button("Delete")){
				std::filesystem::path deletePath = entry.path();  
				bool result = this->fileViewModel.DeleteDirectory(deletePath); 
			}
			ImGui::SameLine();
			if(ImGui::Button("Move")){
				
				
			}
			ImGui::SameLine();
			if(ImGui::Button("New File")){
				
				ImGui::OpenPopup("New File"); 
			}
			if(ImGui::BeginPopup("New File")){

				ImGui::Text("New File Name: ");
				ImGui::SameLine(); 
				bool textInput = ImGui::InputText("##NewName", 
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
			ImGui::SameLine();
			if(ImGui::Button("New Dir")){
				ImGui::OpenPopup("New Dir"); 
			}
			if(ImGui::BeginPopup("New Dir")){
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
					std::filesystem::path entryPath = entry.path(); 	
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
			if(isOpen){
				this->RenderFilesAndDirectories(entry,map);	
				ImGui::TreePop(); 
			}
		
		}
		else{	
			std::filesystem::path entryPath = entry.path();
			ImGui::Text("%s",entryPath.string().c_str());
			ImGui::PushID(entryPath.string().c_str()); 
			ImGui::SameLine();
			if(ImGui::Button("Rename")){
				
					ImGui::OpenPopup("Rename File");
					
			}
				
			static char buffer[256]; 
			if(ImGui::BeginPopup("Rename File")){
				ImGui::Text("New File Name: ");
				ImGui::SameLine(); 
				bool textInput = ImGui::InputText("##NewName", 
					buffer, 
					sizeof(buffer)); 
				ImGui::SameLine(); 
				bool textEntered = ImGui::Button("Ok");
				ImGui::SameLine(); 
				bool canceled = ImGui::Button("Cancel");
				if(textEntered){
					std::string bufferString(buffer);
					this->fileViewModel.RenameFile(entryPath,
								      bufferString);
					ImGui::CloseCurrentPopup();	
				}
				if(canceled){
					ImGui::CloseCurrentPopup();	
				}	
				ImGui::EndPopup();
			}
			ImGui::SameLine(); 
			if(ImGui::Button("Delete")){
				std::filesystem::path deletePath = entry.path();  
				bool result = this->fileViewModel.DeleteFile(deletePath);
			}
			ImGui::SameLine();
			if(ImGui::Button("Move")){


			}
			ImGui::PopID(); 
		}
		ImGui::PopID(); 	
	}
			
}


void FileBrowserWindow::RenderFilesAndDirectories(std::filesystem::directory_entry& entry,
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>>& map){
	
	std::filesystem::path localPath = entry.path(); 
	std::string stringPath = localPath.string(); 
	std::vector<std::filesystem::directory_entry> fileList = map[stringPath.c_str()]; 
	for(std::filesystem::directory_entry localEntry : fileList){
		ImGui::PushID(localEntry.path().string().c_str());
		if(localEntry.is_directory()){
			bool isOpen = ImGui::TreeNode(localEntry.path().string().c_str()); 
			ImGui::SameLine(); 
			if(ImGui::Button("Rename")){
				
				ImGui::OpenPopup("Rename Directory");
			}
			static char buffer[256]; 
			if(ImGui::BeginPopup("Rename Directory")){
				if(ImGui::InputText("New Name for file: ", 
						buffer, 
						sizeof(buffer))){
				
					ImGui::CloseCurrentPopup();	
				}
				
				ImGui::EndPopup();
			}
			ImGui::SameLine();
			if(ImGui::Button("Delete")){
				std::filesystem::path deletePath =localEntry.path();  
				bool result = this->fileViewModel.DeleteDirectory(deletePath);
			}
			ImGui::SameLine();
			if(ImGui::Button("Move")){
			}
			
			ImGui::SameLine();
			if(ImGui::Button("New File")){
				
				ImGui::OpenPopup("New File"); 
			}
			if(ImGui::BeginPopup("New File")){

				ImGui::Text("New File Name: ");
				ImGui::SameLine(); 
				bool textInput = ImGui::InputText("##NewName", 
					buffer, 
					sizeof(buffer)); 
				ImGui::SameLine(); 
				bool textEntered = ImGui::Button("Ok");
				ImGui::SameLine(); 
				bool canceled = ImGui::Button("Cancel");
				if(textEntered){
					
					std::filesystem::path entryPath = localEntry.path(); 
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
			ImGui::SameLine();
			if(ImGui::Button("New Dir")){
				ImGui::OpenPopup("New Dir"); 
			}
			if(ImGui::BeginPopup("New Dir")){
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
					std::filesystem::path entryPath = localEntry.path(); 	
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
			if(isOpen){
				this->RenderFilesAndDirectories(localEntry,map);	
				ImGui::TreePop(); 
			}
		
				 
		}
		else{
			ImGui::Text("%s",localEntry.path().string().c_str());
			ImGui::PushID(localEntry.path().string().c_str()); 
			ImGui::SameLine();
			if(ImGui::Button("Rename")){

				ImGui::OpenPopup("Rename File");
			}
				
			static char buffer[256]; 
			
			if(ImGui::BeginPopup("Rename File")){
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
					ImGui::CloseCurrentPopup();	
				}
				if(canceled){
					ImGui::CloseCurrentPopup();	
				}	
				ImGui::EndPopup();
			}
			ImGui::SameLine();
			if(ImGui::Button("Delete")){
				std::filesystem::path deletePath =localEntry.path();  
				bool result = this->fileViewModel.DeleteFile(deletePath);
			}
			ImGui::SameLine();
			if(ImGui::Button("Move")){


			}
			ImGui::PopID();
		}
		ImGui::PopID(); 
	}	
		
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
