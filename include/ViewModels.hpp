#ifndef VIEWMODELS_HPP
#define VIEWMODELS_HPP 
#include <filesystem> 
#include <fstream> 
#include <string> 
#include <vector> 

class FileViewModel{

	public:
		FileViewModel();
  
		bool NewFile(std::filesystem::path& writeLocation,std::string& objectName);
		
		bool RenameFile(std::filesystem::path& oldPath,std::string& newFileName);

		std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> 
						ReadDirectory(std::filesystem::path& readPath); 

		bool DeleteFile(std::filesystem::path& deletionPath); 			
		
		bool DeleteDirectory(std::filesystem::path& deletionPath);
		
		bool CreateDirectory(std::filesystem::path& creationPath); 
	
		std::filesystem::path& GetProjectRoot(); 	
	
		void SetProjectRoot(std::filesystem::path& newProjectRoot);
			 
	protected:
		std::filesystem::path projectRoot = std::filesystem::current_path(); 
};  

#endif
