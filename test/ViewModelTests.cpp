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
	EXPECT_EQ(expectedContent,output);
}

TEST(FileViewModelTest,ErrorInvalidPath){

	std::filesystem::path writeLocation = std::filesystem::path("nonDir") / "testData" / 
						"ViewModelTest" / "file.txt"; 
	FileViewModel fileViewModel; 
	std::string objectName = std::string("Spells"); 
	EXPECT_FALSE(fileViewModel.NewFile(writeLocation,objectName));
}

TEST(FileViewModelTest,ListFilesAndDirectories){

	std::filesystem::path loadLocation = std::filesystem::path("test") / "testData" / 
						"directoryTestData" / "subDirectoriesWithFiles";
	FileViewModel fileViewModel; 
	std::vector<std::filesystem::directory_entry> result = 
					fileViewModel.ReadDirectory(loadLocation);
	std::vector<std::filesystem::path> expectedPaths;
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


	expectedPaths.push_back(firstPath);
	expectedPaths.push_back(secondPath);
	expectedPaths.push_back(thirdPath); 
	expectedPaths.push_back(fourthPath); 
	expectedPaths.push_back(fifthPath); 
	
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

TEST(FileViewModelTest,BadPathError){

	std::filesystem::path testPath = std::filesystem::path("notReal"); 
	FileViewModel fileViewModel; 
	EXPECT_THROW(fileViewModel.ReadDirectory(testPath),std::filesystem::filesystem_error);

}

TEST(FileViewModelTest,DeleteFile){
	
	std::filesystem::path deletionPath = std::filesystem::path("test") / "testData" /
					     "deleteFileDirectory" / "deleteMe.txt"; 	
	FileViewModel fileViewModel;
	std::string objectName = "Spells";  
	EXPECT_TRUE(fileViewModel.NewFile(deletionPath,objectName));
	EXPECT_TRUE(fileViewModel.DeleteFile(deletionPath));	
}

TEST(FileViewModelTest,DeletePathNonExist){
	std::filesystem::path deletionPath = std::filesystem::path("test") / "testData" /
					     "deleteFileDirectory" / "deleteMe.txt"; 	
	FileViewModel fileViewModel; 
	EXPECT_FALSE(fileViewModel.DeleteFile(deletionPath));	
}

TEST(FileViewModelTest,DeleteDirectory){
	
	std::filesystem::path deletionPath = std::filesystem::path("test") / "testData" /
					     "deleteFileDirectory" ; 	
	FileViewModel fileViewModel; 
	EXPECT_FALSE(fileViewModel.DeleteFile(deletionPath));	

}

TEST(FileViewModelTest,DeleteDirectoryMethod){

	std::filesystem::path deletionPath = std::filesystem::path("test") / "testData" /
					     "deleteDirectory" / "deleteMe.txt";
	std::filesystem::path directoryCreationPath = std::filesystem::path("test") / 
						"testData" / "deleteDirectory"; 		
	std::filesystem::create_directory(directoryCreationPath);
	std::ofstream file(deletionPath);
	EXPECT_TRUE(file);
	FileViewModel fileViewModel;
	bool result = fileViewModel.DeleteDirectory(directoryCreationPath);
	EXPECT_TRUE(result);
}

TEST(FileViewModelTest,DeleteNonDirectory){

	std::filesystem::path directoryCreationPath = std::filesystem::path("test") / 
						"testData" / "deleteDirectory"; 
	
	FileViewModel fileViewModel;
	bool result = fileViewModel.DeleteDirectory(directoryCreationPath);
	EXPECT_FALSE(result);	
}

TEST(FileViewModelTest,RenameFile){

	std::filesystem::path renameFilePath = std::filesystem::path("test") / 
						"testData" / "renameFile" / "changeMe.txt";
	
	FileViewModel fileViewModel; 
	std::string newName = std::string("newName.txt");
	bool result = fileViewModel.RenameFile(renameFilePath,newName);
	EXPECT_TRUE(result);
	std::filesystem::path newPathName = std::filesystem::path("test") / 
						"testData" / "renameFile" / newName;
	bool fileExists = std::filesystem::exists(newPathName);
	EXPECT_TRUE(fileExists);
	std::ofstream file(renameFilePath);
	
	EXPECT_TRUE(file);		
}

TEST(FileViewModelTest,RenameFilePathNotExist){
	
	std::filesystem::path renameFilePath = std::filesystem::path("test") / 
						"testData" / "renameFile" / "noExist.txt";
	
	FileViewModel fileViewModel; 
	std::string newName = std::string("newName.txt");
	bool result = fileViewModel.RenameFile(renameFilePath,newName);	
	EXPECT_FALSE(result);	
}

TEST(FileViewModelTest,InitialProjectRoot){

	std::filesystem::path oldPath = std::filesystem::current_path();
	FileViewModel fileViewModel; 
	std::filesystem::path initializationPath = fileViewModel.GetProjectRoot(); 
	EXPECT_EQ(oldPath,initializationPath);
}

TEST(FileViewModelTest,SetProjectRoot){

	std::filesystem::path newPath = std::filesystem::path("test");
	FileViewModel fileViewModel; 
	fileViewModel.SetProjectRoot(newPath); 
	std::filesystem::path projectRootResult = fileViewModel.GetProjectRoot(); 
	EXPECT_EQ(newPath,projectRootResult);	 
}

TEST(FileViewModelTest,CreateDirectory){
		
	std::filesystem::path writePath = std::filesystem::path("test") / "testData" / 
						"makeDirectory" ; 
	std::filesystem::path newDirectory = std::filesystem::path(writePath) / "NewDir"; 
	FileViewModel fileViewModel; 
	bool result = fileViewModel.CreateDirectory(newDirectory);
	EXPECT_TRUE(result);
	bool existanceCheck = std::filesystem::exists(newDirectory);
	EXPECT_TRUE(existanceCheck);    
	if(result == true){
		
		fileViewModel.DeleteDirectory(newDirectory); 
	}
	
}

TEST(FileViewModelTest,CreateDirectoryNonExistance){
		
	std::filesystem::path writePath = std::filesystem::path("FakeDir") / "testData" / 
						"makeDirectory" ; 
	FileViewModel fileViewModel; 
	EXPECT_THROW(fileViewModel.CreateDirectory(writePath),std::filesystem::filesystem_error);
	bool existanceCheck = std::filesystem::exists(writePath);
	EXPECT_FALSE(existanceCheck);    
	if(existanceCheck == true){
		
		fileViewModel.DeleteDirectory(writePath); 
	}
	
}
