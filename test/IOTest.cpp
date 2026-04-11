#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../include/IO.hpp"

TEST(TrivialTest,AlwaysPasses){

	EXPECT_TRUE(true); 

}

TEST(IOTest,EmptyDirectory){

	std::filesystem::path testPath = std::filesystem::path("test")
				 / "testData" / "directoryTestData" / "emptyDirectory" ; 
	DirectoryData directoryData(testPath); 
	std::vector<std::filesystem::directory_entry> result = directoryData.GetDirectoryData(); 
	int size = result.size(); 
	EXPECT_EQ(0,size); 
}
