#include "../include/IO.hpp"
#include <vector>
#include <filesystem>

DirectoryData::DirectoryData(std::filesystem::path& rootPath):rootPath(rootPath){}

std::vector<std::filesystem::directory_entry>& DirectoryData::GetDirectoryData(){

	for(const std::filesystem::directory_entry& entry : 
			std::filesystem::directory_iterator(this->rootPath)){
		this->directoryData.push_back(entry);
	}
	return this->directoryData; 
}
