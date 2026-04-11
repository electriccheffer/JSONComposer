#ifndef IO_HPP
#define IO_HPP 
#include <vector>
#include <filesystem>

class DirectoryData{

	public:
		DirectoryData(std::filesystem::path& rootPath);
		std::vector<std::filesystem::directory_entry>& GetDirectoryData(); 	
	protected: 
		std::vector<std::filesystem::directory_entry> directoryData; 		
		std::filesystem::path& rootPath; 		

}; 

#endif
