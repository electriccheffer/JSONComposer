#include "../include/Windows.hpp"
#include "../include/IO.hpp"
#include "../include/ViewModels.hpp"

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
	FileViewModel fileViewModel; 
	std::filesystem::path projectRoot = fileViewModel.GetProjectRoot(); 
	DirectoryData directoryData(projectRoot);
	std::vector<std::filesystem::directory_entry> directoryDataList = 
								directoryData.GetDirectoryData();
	
	std::string rootPathString = "Project Root: " + projectRoot.string();
	ImGui::Text("%s" ,rootPathString.c_str());
	ImGui::SameLine(); 
	ImGui::Button("Change Project Root"); 	
	ImGui::Text("-FILE EXPLORER-");
	this->RenderFilesAndDirectories(directoryDataList);		
	ImGui::End();
}

void FileBrowserWindow::RenderFilesAndDirectories(
				std::vector<std::filesystem::directory_entry>& directoryDataList){
	
	int length = directoryDataList.size();
	//TODO: Start adding buttons 
	for(int i = 0 ; i < length ; i++){
		std::filesystem::directory_entry entry = directoryDataList[i]; 
		std::filesystem::path filePath(entry.path());
		std::string pathString(filePath.string());	
		if(entry.is_directory()){
			ImGui::PushID(pathString.c_str());	
			bool isOpen = ImGui::TreeNode(pathString.c_str()); 
			ImGui::SameLine();	
			ImGui::Button("Rename");
			ImGui::SameLine();	
			ImGui::Button("Delete");
			ImGui::SameLine();	
			ImGui::Button("Move");
			ImGui::SameLine();	
			ImGui::Button("New File");
			ImGui::SameLine();	
			ImGui::Button("New Directory");
			if(isOpen){
				
				
				if(i == length - 1){
					ImGui::TreePop(); 
					ImGui::PopID(); 
					break; 
				}
				
				for(int j = i+1 ; j < length  ; j++){
					
					std::filesystem::directory_entry 
							fileEntry(directoryDataList[j]); 
					std::filesystem::path 
						directorySubFilePath(fileEntry.path()); 
					if(fileEntry.is_directory()){
						i = j - 1; 
						break; 
					}
					std::string 
						subFilePathString(directorySubFilePath.string()); 
					ImGui::Text("%s",subFilePathString.c_str()); 
				}	
				ImGui::TreePop(); 	
			}
			ImGui::PopID();
		}
		else{
			ImGui::Text("%s",pathString.c_str()); 
		}	
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
