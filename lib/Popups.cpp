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


MoveDirectoryPopup::MoveDirectoryPopup(std::unordered_map
			<std::string,std::vector<std::filesystem::directory_entry>>& directoryMap,
			std::filesystem::path& projectRoot,
			std::filesystem::path& sourceDirectory)
			:directoryMap(directoryMap),projectRoot(projectRoot),
			sourceDirectory(sourceDirectory){}

void MoveDirectoryPopup::Render(){
	
	ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_Always);
	if(ImGui::BeginPopup("Move Directory")){
		ImGui::Text("MOVE TO");	
		std::string stringRootPath = this->projectRoot.string(); 
		std::vector<std::filesystem::directory_entry> directoryContents = 
							this->directoryMap[stringRootPath];	

		for(std::filesystem::directory_entry entry : directoryContents){
			
			if(entry.is_directory()){
		
				std::filesystem::path entryPath = entry.path(); 
				this->RenderHelper(entryPath);			

			}	
		}
		if(destination != ""){
			std::string moveTo("Destination: %s"); 
			ImGui::Text(moveTo.c_str(),this->destination.c_str() );
		}	
		else{

			ImGui::Text("Destination: "); 
		}
		if(ImGui::Button("Ok")){
			
			FileViewModel fileViewModel; 	
			std::filesystem::path destinationPath(this->destination); 
			fileViewModel.MoveDirectory(this->sourceDirectory,destinationPath);	
		} 
		ImGui::SameLine(); 
		if(ImGui::Button("Cancel")){
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::EndPopup(); 
	}
	
}


void MoveDirectoryPopup::RenderHelper(std::filesystem::path filePath){

	std::string stringPath = filePath.string(); 	
		
	std::vector<std::filesystem::directory_entry> contentsList = 
						this->directoryMap[stringPath];
			
	bool open = ImGui::TreeNode(stringPath.c_str()); 
				
	if(open){
		this->destination = stringPath; 	
		for(std::filesystem::directory_entry entry : contentsList){
			if(entry.is_directory()){
				this->RenderHelper(entry.path()); 
			}	
			
		}	
			
		ImGui::TreePop();
	}		
	
	
}

MoveFilePopup::MoveFilePopup(std::unordered_map<
			std::string,std::vector<std::filesystem::directory_entry>>& directoryMap,
			std::filesystem::path& projectRoot, std::filesystem::path& sourceFile):
			map(directoryMap),projectRoot(projectRoot),sourceFile(sourceFile){} 


void MoveFilePopup::Render(){

	std::vector<std::filesystem::directory_entry> topDirectoryContents = 
							map[this->projectRoot.string()];
	
	if(ImGui::BeginPopup("Move File")){

		for(std::filesystem::directory_entry entry : topDirectoryContents){
			
				if(entry.is_directory()){
				
					std::filesystem::path entryPath = entry.path(); 
					this->RenderHelper(entryPath); 
				}

		}
		if(this->destination != ""){
			
			ImGui::Text("Move to: %s",this->destination.c_str());
		}
		else{

			ImGui::Text("Move to: ");
		}
		if(ImGui::Button("Ok")){
			
			FileViewModel fileViewModel;
			//Add the operation

		}
		ImGui::SameLine(); 
		if(ImGui::Button("Cancel")){
			
			ImGui::CloseCurrentPopup(); 
		}	
		ImGui::EndPopup(); 
	}
		
	
}

void MoveFilePopup::RenderHelper(std::filesystem::path entry){

	std::vector<std::filesystem::directory_entry> subDirectoryContents = 
								this->map[entry.string()]; 

			
		bool isOpen = ImGui::TreeNode(entry.string().c_str()); 
		if(isOpen){
			this->destination = entry.string(); 
			for(std::filesystem::directory_entry entry : subDirectoryContents){
			
				if(entry.is_directory()){
					
					this->RenderHelper(entry);
				}
		
			}
			ImGui::TreePop(); 
		}
	
}
