#include "../include/ViewModels.hpp"
#include "../include/IO.hpp"
#include <filesystem> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <unordered_map> 
#include <iostream> 

FileViewModel::FileViewModel(){}

bool FileViewModel::NewFile(std::filesystem::path& writeLocation,std::string& objectName){
	
	std::filesystem::path newPath = writeLocation / objectName; 	
	std::ofstream file(newPath); 
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

std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>>
		 		FileViewModel::ReadDirectory(std::filesystem::path& readPath){

	DirectoryData directoryData(readPath); 
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> result; 
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

bool FileViewModel::RenameDirectory(std::filesystem::path& oldPathName,
				    std::string& newDirectoryName){
	
	bool directoryExists = std::filesystem::exists(oldPathName); 
	if(!directoryExists){

		return false; 
	}
	try{
		std::filesystem::path newPathName(oldPathName); 
		newPathName.replace_filename(newDirectoryName);
		std::filesystem::rename(oldPathName,newPathName);
		bool success = std::filesystem::exists(newPathName);
		if(success){
			return true; 
		}
		else{
			return false; 
		}
	}
	catch(const std::filesystem::filesystem_error errorMessage){
		throw errorMessage; 
	}	
	return false; 

}

bool FileViewModel::CreateDirectory(std::filesystem::path& creationPath,
			            std::string& newDirectoryName){
	
	creationPath /= newDirectoryName; 	
	bool result = false; 	
	try{
		result = std::filesystem::create_directory(creationPath);
	}
	catch(std::filesystem::filesystem_error fileError){
		
		throw fileError; 

	}	
	return result;  	
	
}

bool FileViewModel::MoveDirectory(std::filesystem::path& source,
				 std::filesystem::path& destination){
	
	bool sourceExists = std::filesystem::exists(source);
	bool destinationExists = std::filesystem::exists(destination);
	
	if(!sourceExists){
		return false; 
	} 	
	if(!destinationExists){
	
		return false; 
	}
	
	bool isSourceDirectory = std::filesystem::is_directory(source);
	bool isDestinationDirectory = std::filesystem::is_directory(destination); 
	
	if(!isSourceDirectory){
		return false; 
	}
	if(!isDestinationDirectory){
		return false; 
	}
	try{
		std::filesystem::path newDestination = destination / source.filename(); 
		std::filesystem::rename(source,newDestination);
		return true; 
	}
	catch(const std::filesystem::filesystem_error fileError){
		std::filesystem::path newDestination = destination / source.filename(); 
		std::filesystem::copy(source,newDestination
					,std::filesystem::copy_options::recursive); 
		std::filesystem::remove_all(source);
		return true; 
	}	
		
}

std::filesystem::path& FileViewModel::GetProjectRoot(){

	return this->projectRoot; 
}

void FileViewModel::SetProjectRoot(std::filesystem::path& newProjectRoot){

	this->projectRoot = newProjectRoot; 
}
