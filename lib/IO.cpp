#include "../include/IO.hpp"
#include <vector>
#include <filesystem>
#include <unordered_map>

DirectoryData::DirectoryData(std::filesystem::path& rootPath):rootPath(rootPath){}

std::unordered_map<std::string,std::vector <std::filesystem::directory_entry>>& 
						DirectoryData::GetDirectoryData(){
	
	std::filesystem::directory_entry rootDirectoryEntry(rootPath);
	std::filesystem::path rootDirectoryPath = rootDirectoryEntry.path(); 
	std::string stringPath = rootDirectoryPath.string(); 
	this->directoryData[stringPath] = 
				std::vector<std::filesystem::directory_entry>();  
	try{	
		for(const std::filesystem::directory_entry& entry : 
				std::filesystem::recursive_directory_iterator(this->rootPath)){
		
			if(entry.is_directory()){
				
				//Get the parent directory entry 
				std::vector<std::filesystem::directory_entry> fileList; 
				std::filesystem::path entryPath = entry.path();  
				std::filesystem::path parentPath = entryPath.parent_path();
				std::string parentPathString = parentPath.string(); 
				
				//Get the list for the parent and add the directory to it  
				std::vector<std::filesystem::directory_entry> existingList = 
							directoryData[parentPathString]; 
				existingList.push_back(entry);
				directoryData[parentPathString] = existingList; 
					
				//Make new list for the directory entry
				std::string entryPathString = entryPath.string(); 
				directoryData[entryPathString] =
					std::vector<std::filesystem::directory_entry>();
				 
			}
			else{
				//Get the parent directory entry
				std::filesystem::path entryPath = entry.path();
				std::string entryStringPath = entryPath.string(); 
				std::filesystem::directory_entry parentEntry =
						std::filesystem::directory_entry(
								entryPath.parent_path());
				std::filesystem::path parentPath = parentEntry.path(); 
				std::filesystem::path parentPathString = parentPath.string(); 
				
				//Get the list for the existing 
				std::vector<std::filesystem::directory_entry> fileList  = 
								directoryData[parentPathString];
				fileList.push_back(entry);
				directoryData[parentPathString] = fileList; 	
			}	
		}
		
	}
	catch(const std::filesystem::filesystem_error fileError ){
		this->directoryData.clear(); 
		throw fileError; 
		
	}
	return this->directoryData; 
}
