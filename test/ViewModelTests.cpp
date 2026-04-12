#include <gtest/gtest.h>
#include <filesystem>
#include "../include/ViewModels.hpp"
#include <fstream> 
#include <string> 
#include <sstream> 
#include <iostream> 

TEST(ViewModelTrivialTest,AlwaysPasses){

	EXPECT_TRUE(true); 
}

TEST(FileViewModelTest,WriteFile){

	std::filesystem::path writeLocation = std::filesystem::path("test") / "testData" / 
						"ViewModelTest" / "file.txt"; 
	FileViewModel fileViewModel;
	std::string objectName = std::string("Spells"); 
	EXPECT_TRUE(fileViewModel.NewFile(writeLocation,objectName));
	std::string expectedContent = std::string("{\"") + "Spells" + "\":[]}"; 
	std::ifstream file(writeLocation);
	std::stringstream buffer; 
	buffer << file.rdbuf();
	std::string output = buffer.str();  
	EXPECT_TRUE(std::filesystem::exists(writeLocation)); 
	std::filesystem::remove(writeLocation);
	std::cout << output << std::endl;  	
	EXPECT_EQ(expectedContent,output);
}

TEST(FileViewModelTest,ErrorInvalidPath){

	std::filesystem::path writeLocation = std::filesystem::path("nonDir") / "testData" / 
						"ViewModelTest" / "file.txt"; 
	FileViewModel fileViewModel; 
	std::string objectName = std::string("Spells"); 
	EXPECT_FALSE(fileViewModel.NewFile(writeLocation,objectName));
}
