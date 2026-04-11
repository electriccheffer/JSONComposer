#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../include/IO.hpp"
#include <iostream> 

TEST(TrivialTest,AlwaysPasses){

	EXPECT_TRUE(true); 
}

TEST(DirectoryData,EmptyDirectory){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "emptyDirectory" ; 
	DirectoryData directoryData(testPath); 
	std::vector<std::filesystem::directory_entry> result = directoryData.GetDirectoryData(); 
	int size = result.size(); 
	EXPECT_EQ(0,size); 
}

TEST(DirectoryData,FilesOnlyDirectory){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "filesOnlyDirectory" ; 
	DirectoryData directoryData(testPath);
	std::vector<std::filesystem::directory_entry> result = directoryData.GetDirectoryData(); 
	std::vector<std::filesystem::path> expectedPaths; 
	std::filesystem::path firstPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileOne.txt" ;
	std::filesystem::path secondPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileTwo.txt" ;
	std::filesystem::path thirdPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileThree.txt" ;
	expectedPaths.push_back(firstPath);
	expectedPaths.push_back(secondPath); 
	expectedPaths.push_back(thirdPath); 
	int count = 0; 
	int size = result.size(); 
	int expectedSize = expectedPaths.size(); 

	for(int i = 0 ; i < size ; i++){
		for(int k = 0 ; k < expectedSize  ; k++){
			
			if(result[i].path().string() == expectedPaths[k].string()){
				count++; 
			}	

		}
	}
	EXPECT_EQ(3,count); 
}

TEST(DirectoryData,Subdirectories){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "subDirectories" ; 
	DirectoryData directoryData(testPath);
	std::vector<std::filesystem::directory_entry> result = directoryData.GetDirectoryData(); 
	std::vector<std::filesystem::path> expectedPaths; 
	std::filesystem::path firstPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"subDirectories" / "dirOne" ;
	std::filesystem::path secondPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectories" / "dirTwo" ;
	std::filesystem::path thirdPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectories" /"dirOne" /"dirThree" ;

	expectedPaths.push_back(firstPath);
	expectedPaths.push_back(secondPath);
	expectedPaths.push_back(thirdPath); 

	int count = 0; 
	int size = result.size(); 
	int expectedSize = expectedPaths.size(); 

	for(int i = 0 ; i < size ; i++){
		for(int k = 0 ; k < expectedSize  ; k++){
			
			if(result[i].path().string() == expectedPaths[k].string()){
				count++; 
			}	

		}
	}
	EXPECT_EQ(size,count); 


}
