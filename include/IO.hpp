#ifndef IO_HPP
#define IO_HPP 
#include <vector>
#include <filesystem>
#include <unordered_map> 

class DirectoryData{

	public:
		DirectoryData(std::filesystem::path& rootPath);
		std::unordered_map<std::string,
			     std::vector<std::filesystem::directory_entry>>& GetDirectoryData();
	protected: 
		std::unordered_map<std::string,
			     std::vector<std::filesystem::directory_entry>> directoryData;
		std::filesystem::path& rootPath; 		

}; 

#endif
