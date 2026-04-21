#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../include/IO.hpp"
#include <iostream> 

TEST(IOTrivialTest,AlwaysPasses){

	EXPECT_TRUE(true); 
}

TEST(DirectoryData,EmptyDirectory){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "emptyDirectory" ; 
	DirectoryData directoryData(testPath); 
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> result = 
							directoryData.GetDirectoryData(); 
	int size = result.size(); 
	EXPECT_EQ(1,size); 
}

TEST(DirectoryData,FilesOnlyDirectory){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "filesOnlyDirectory" ; 
	DirectoryData directoryData(testPath);
	
	std::vector<std::filesystem::directory_entry> expectedPaths; 
	std::filesystem::path firstPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileOne.txt" ;
	std::filesystem::path secondPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileTwo.txt" ;
	std::filesystem::path thirdPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"filesOnlyDirectory" / "fileThree.txt" ;
	expectedPaths.push_back(std::filesystem::directory_entry(firstPath));
	expectedPaths.push_back(std::filesystem::directory_entry(secondPath)); 
	expectedPaths.push_back(std::filesystem::directory_entry(thirdPath)); 
	
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> map = 
							directoryData.GetDirectoryData();  
	std::vector<std::filesystem::directory_entry> resultList = map[testPath.string()]; 
	
	
	int count = 0; 
	int size = resultList.size(); 
	int expectedSize = expectedPaths.size(); 
	for(int i = 0 ; i < size ; i++){
		for(int k = 0 ; k < expectedSize  ; k++){
			
			if(resultList[i].path().string() == expectedPaths[k].path().string()){
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
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> map = 
							directoryData.GetDirectoryData();  
	std::vector<std::filesystem::directory_entry> resultList = map[testPath.string()]; 

 
	std::filesystem::path firstPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"subDirectories" / "dirOne" ;
	std::filesystem::path secondPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectories" / "dirTwo" ;
	std::filesystem::path thirdPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectories" /"dirOne" /"dirThree" ;
	
	for(std::filesystem::directory_entry entry : resultList){
		
		std::filesystem::path entryPath = entry.path(); 
		std::string entryPathString = entryPath.string(); 
		if(entryPathString == firstPath.string()){
			continue; 	
		}
		else if(entryPathString == secondPath.string()){
		
			continue; 	
		}
		else{
			EXPECT_TRUE(false);
		}	
		
	} 
	
	EXPECT_EQ(2,map[testPath.string()].size() );
	EXPECT_EQ(1,map[firstPath.string()].size());  
	EXPECT_EQ(0,map[thirdPath.string()].size());	
}

TEST(DirectoryData,SubdirectoriesWithFiles){
	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "subDirectoriesWithFiles" ; 
	DirectoryData directoryData(testPath);
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> result = 
						directoryData.GetDirectoryData(); 
	
	std::filesystem::path firstPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"subDirectoriesWithFiles" / "dirOne" ;
	std::filesystem::path secondPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectoriesWithFiles" / "dirTwo" ;
	std::filesystem::path thirdPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectoriesWithFiles" /"fileThree.txt";
	std::filesystem::path fourthPath = std::filesystem::path("test") / 
					"testData" / "directoryTestData" / 
					"subDirectoriesWithFiles" / "dirOne" / "fileOne.txt" ;
	std::filesystem::path fifthPath = std::filesystem::path("test") 
					/ "testData" / "directoryTestData" / 
					"subDirectoriesWithFiles" / "dirTwo" / "fileTwo.txt" ;
	
	std::vector<std::filesystem::directory_entry> topList = result[testPath.string()]; 
	std::vector<std::filesystem::directory_entry> dirOneList = result[firstPath.string()]; 
	std::vector<std::filesystem::directory_entry> dirTwoList = result[secondPath.string()];
	EXPECT_EQ(3,topList.size());
	EXPECT_EQ(1,dirOneList.size());
	EXPECT_EQ(1,dirTwoList.size());
}

TEST(DirectoryData,InvalidPath){
	
	std::filesystem::path testPath = std::filesystem::path("notReal"); 
	DirectoryData directoryData(testPath);
	EXPECT_THROW(directoryData.GetDirectoryData(),std::filesystem::filesystem_error);
}

