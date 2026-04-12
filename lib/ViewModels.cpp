#include "../include/ViewModels.hpp"
#include <filesystem> 
#include <fstream> 
#include <string> 

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
