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

	bool result = std::filesystem::remove(deletionPath);		

	return result; 	

}
