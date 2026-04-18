#include "../include/ViewModels.hpp"
#include "../include/IO.hpp"
#include <filesystem> 
#include <fstream> 
#include <string> 
#include <vector> 

FileViewModel::FileViewModel(){}

bool FileViewModel::NewFile(std::filesystem::path& writeLocation,std::string& objectName){
	
	std::ofstream file(writeLocation); 
	std::string writeData = std::string("{\"") + objectName + "\":[]}"; 
	if(!file.is_open()){
		return false; 	
	}
	file << writeData;
	if(!file){
		return false;
	}	
	return true;  		
}

bool FileViewModel::RenameFile(std::filesystem::path& oldPath,std::string& newFileName){


	bool fileExists = std::filesystem::exists(oldPath);	
	if(!fileExists){
		return false; 
	}
	std::filesystem::path oldPathReference(oldPath);	
	std::filesystem::path newPath = oldPathReference.replace_filename(newFileName);
	std::filesystem::rename(oldPath,newPath); 
	bool result = std::filesystem::exists(newPath);
	return result; 
}

std::vector<std::filesystem::directory_entry> FileViewModel::ReadDirectory(
						std::filesystem::path& readPath){

	DirectoryData directoryData(readPath); 
	std::vector<std::filesystem::directory_entry> result; 
	try{
		result = directoryData.GetDirectoryData(); 
	}
	catch(const std::filesystem::filesystem_error fileError){

		throw fileError; 
	}
	return result; 	
}

bool FileViewModel::DeleteFile(std::filesystem::path& deletionPath){
	
	bool isDirectory = std::filesystem::is_directory(deletionPath);
	
	if(isDirectory){
		return false; 
	}
	
	bool result = std::filesystem::remove(deletionPath);		

	return result; 	

}

bool FileViewModel::DeleteDirectory(std::filesystem::path& deletionPath){

	int numberRemoved =  std::filesystem::remove_all(deletionPath);
	if(numberRemoved == 0){
		return false; 
	}
	return true; 
}


bool FileViewModel::CreateDirectory(std::filesystem::path& creationPath){
	
	bool result = false; 	
	try{
		result = std::filesystem::create_directory(creationPath);
	}
	catch(std::filesystem::filesystem_error fileError){
		
		throw fileError; 

	}	
	return result;  	
	
}

std::filesystem::path& FileViewModel::GetProjectRoot(){

	return this->projectRoot; 
}

void FileViewModel::SetProjectRoot(std::filesystem::path& newProjectRoot){

	this->projectRoot = newProjectRoot; 
}
