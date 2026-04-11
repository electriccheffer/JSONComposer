#include "../include/IO.hpp"
#include <vector>
#include <filesystem>

DirectoryData::DirectoryData(std::filesystem::path& rootPath):rootPath(rootPath){}

std::vector<std::filesystem::directory_entry>& DirectoryData::GetDirectoryData(){
	
	try{	
		for(const std::filesystem::directory_entry& entry : 
			std::filesystem::recursive_directory_iterator(this->rootPath)){
				this->directoryData.push_back(entry);
		}
	}
	catch(const std::filesystem::filesystem_error fileError ){

		throw fileError; 
		
	}
	return this->directoryData; 
}
