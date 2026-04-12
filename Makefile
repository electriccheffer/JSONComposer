buildDirectory = ./build

sourceDirectory = ./src

libraryDirectory = ./lib

testDirectory = ./test

CXXFlags = -std=c++17 -Iinclude

thirdPartyDirectory = ./third_party/imgui

testCompileOptions =  -I/opt/homebrew/opt/googletest/include -L/opt/homebrew/opt/googletest/lib\
	-lgtest -lgtest_main -pthread

buildFiles = $(sourceDirectory)/main.cpp \
	     third_party/imgui/imgui.cpp \
	     third_party/imgui/imgui_draw.cpp \
	     third_party/imgui/imgui_tables.cpp \
	     third_party/imgui/imgui_widgets.cpp \
	     third_party/imgui/backends/imgui_impl_glfw.cpp \
	     third_party/imgui/backends/imgui_impl_opengl3.cpp \
	     $(libraryDirectory)/Windows.cpp
	     

executable = $(buildDirectory)/main

compileOptions =-std=c++17 -I/opt/homebrew/opt/glfw/include \
		-Ithird_party/imgui \
		-Ithird_party/imgui/backends \
		-L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL\
		-framework Cocoa -framework IOKit -framework CoreVideo -o

testFiles = $(libraryDirectory)/IO.cpp \
	    $(libraryDirectory)/ViewModels.cpp 

testScripts = $(testDirectory)/IOTest.cpp \
	      $(testDirectory)/ViewModelTests.cpp

testObjectFiles = $(buildDirectory)/IO.o \
		  $(buildDirectory)/ViewModels.o

testTarget = $(buildDirectory)/test_runner

build: $(executable)
	$(executable)
	make clean

test: $(testTarget)
	$(testTarget) --gtest_color=yes
	rm -f $(buildDirectory)/*

clean: 
	rm -f $(executable)

$(testTarget):$(testObjectFiles)
	g++ $(CXXFlags) $(testScripts)  $(testObjectFiles) \
	-o $(buildDirectory)/test_runner $(testCompileOptions)	

$(testObjectFiles): $(testFiles)
	g++ $(CXXFlags) -c $(libraryDirectory)/IO.cpp -o $(buildDirectory)/IO.o
	g++ $(CXXFlags) -c $(libraryDirectory)/ViewModels.cpp -o $(buildDirectory)/ViewModels.o
	
$(executable): $(buildFiles)
	g++ $(buildFiles) $(compileOptions) $(executable)
