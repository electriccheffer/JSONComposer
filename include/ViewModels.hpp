#ifndef VIEWMODELS_HPP
#define VIEWMODELS_HPP 
#include <filesystem> 
#include <fstream> 
#include <string> 

class FileViewModel{

	public:
		FileViewModel();  
		bool NewFile(std::filesystem::path& writeLocation,std::string& objectName);
	protected:
};  

#endif
