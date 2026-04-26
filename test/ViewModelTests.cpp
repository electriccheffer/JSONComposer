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
						"ViewModelTest"; 
	FileViewModel fileViewModel;
	std::string objectName = std::string("Spells"); 
	EXPECT_TRUE(fileViewModel.NewFile(writeLocation,objectName));
	std::string expectedContent = std::string("{\"") + "Spells" + "\":[]}"; 
	std::ifstream file(writeLocation / objectName);
	std::stringstream buffer; 
	buffer << file.rdbuf();
	std::string output = buffer.str();  
	EXPECT_TRUE(std::filesystem::exists(writeLocation)); 
	std::filesystem::remove(writeLocation / objectName);
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
	std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> result = 
					fileViewModel.ReadDirectory(loadLocation);
	
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
	
	std::vector<std::filesystem::directory_entry> topList = result[loadLocation.string()]; 
	EXPECT_EQ(3,topList.size());

}

TEST(FileViewModelTest,BadPathError){

	std::filesystem::path testPath = std::filesystem::path("notReal"); 
	FileViewModel fileViewModel; 
	EXPECT_THROW(fileViewModel.ReadDirectory(testPath),std::filesystem::filesystem_error);

}

TEST(FileViewModelTest,DeleteFile){
	
	std::filesystem::path deletionPath = std::filesystem::path("test") / "testData" /
					     "deleteFileDirectory"; 	
	FileViewModel fileViewModel;
	std::string objectName = "Spells";  
	EXPECT_TRUE(fileViewModel.NewFile(deletionPath,objectName));
	deletionPath /= objectName; 
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
	std::string newDirectoryName = "NewDir"; 
	std::filesystem::path newDirectory = std::filesystem::path(writePath); 
	FileViewModel fileViewModel; 
	bool result = fileViewModel.CreateDirectory(newDirectory,newDirectoryName);
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
	std::string newDirectoryName = "NewDir"; 
	FileViewModel fileViewModel; 
	EXPECT_THROW(fileViewModel.CreateDirectory(writePath,newDirectoryName),
					std::filesystem::filesystem_error);
	bool existanceCheck = std::filesystem::exists(writePath);
	EXPECT_FALSE(existanceCheck);    
	if(existanceCheck == true){
		
		fileViewModel.DeleteDirectory(writePath); 
	}
	
}

TEST(FileViewModelTest,RenameDirectoryNormalCase){

	
	std::filesystem::path renamePath = std::filesystem::path("test") / "testData" 
					   / "renameDirectory"; 
	std::string newName = "newName"; 
	
	FileViewModel fileViewModel; 
	bool result = fileViewModel.RenameDirectory(renamePath,newName);
	EXPECT_TRUE(result);
	
	std::filesystem::path pathResult = std::filesystem::path("test") / "testData" 
					   / "newName";
	std::filesystem::directory_entry renamedTarget(pathResult);
	bool pathExists = renamedTarget.exists(); 
	EXPECT_TRUE(pathExists);
	try{

		std::filesystem::rename(pathResult,renamePath);
	}
	catch(const std::filesystem::filesystem_error& errorMessage){
		
		std::cout << errorMessage.what() << std::endl; 
		EXPECT_TRUE(false);
	}
}

TEST(FileViewModelTest,RenameDirectoryNonExist){
	
	std::filesystem::path nonExist("noExist");
	FileViewModel fileViewModel; 
	std::string newName = "IDK"; 
	bool result = fileViewModel.RenameDirectory(nonExist,newName);
	EXPECT_FALSE(result);
	

}

TEST(FileViewModelTest,MoveDirectoryDestinationEmpty){
	
	std::filesystem::path source = std::filesystem::path("test") / "testData" 
					   / "moveDirectory" / "source";
	
	std::filesystem::path destination = std::filesystem::path("test") / "testData" 
					   / "moveDirectory" / "destination"; 
	 
	std::filesystem::path destinationExpected = std::filesystem::path("test") / "testData"
					  / "moveDirectory" / "destination" / "source" 
					  / "file.txt"; 	
	std::filesystem::path resetSource = std::filesystem::path("test") / "testData"
					  / "moveDirectory" / "destination" / "source"; 
	
	std::filesystem::path resetDestination = std::filesystem::path("test") / "testData"
						/ "moveDirectory" / "source"; 
	FileViewModel fileViewModel; 
	bool output = fileViewModel.MoveDirectory(source,destination); 	
	EXPECT_TRUE(output); 

	bool success = std::filesystem::exists(destinationExpected);
	EXPECT_TRUE(success);
	
	std::filesystem::path resetPath = std::filesystem::path("test") / "testData" 
					  / "moveDirectory" / "source";
	std::filesystem::rename(resetSource,resetDestination);
	
	std::filesystem::path sourceResetExpected = std::filesystem::path("test") / "testData"
						   / "moveDirectory" / "source" / "file.txt";
	
	bool resetSuccess = std::filesystem::exists(sourceResetExpected);
	
	EXPECT_TRUE(resetSuccess); 
	
}
	
TEST(FileViewModelTest,MoveDirectoryDestinationNonEmpty){
	
	std::filesystem::path source = std::filesystem::path("test") / "testData" / "moveDirectory"
					/ "emptySource"; 

	std::filesystem::path destination = std::filesystem::path("test") / "testData" / 
					    "moveDirectory" / "nonEmptyDestination"; 
	
	FileViewModel fileViewModel; 
	bool success = fileViewModel.MoveDirectory(source,destination);
	EXPECT_TRUE(success);
	
	std::filesystem::path expectedPath = std::filesystem::path("test") / "testData" / 
						"moveDirectory" / "nonEmptyDestination" / 
						"emptySource";
	bool expectedOutcome = std::filesystem::exists(expectedPath);
	
	EXPECT_TRUE(expectedOutcome);
	
	std::filesystem::rename(expectedPath,source);
		
	bool resetSuccess = std::filesystem::exists(source);
	
	EXPECT_TRUE(resetSuccess); 
	
}

TEST(FileViewModelTest,MoveDirectoryFileSource){
	
	std::filesystem::path fileSource = std::filesystem::path("test") / "testData" / 
					  "moveDirectory"/  "nonEmptyDestination" / "file.txt"; 
	std::filesystem::path destination = std::filesystem::path("test") / "testData" / 
						"moveDirectory" / "source"; 
	FileViewModel fileViewModel; 
	bool result = fileViewModel.MoveDirectory(fileSource,destination);
	EXPECT_FALSE(result); 
		
}
