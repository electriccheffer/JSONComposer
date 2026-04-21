#include <iostream>
#include <GLFW/glfw3.h>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/backends/imgui_impl_opengl3.h"
#include "../third_party/imgui/backends/imgui_impl_glfw.h"
#include "../include/Windows.hpp"
#include <filesystem>

int main(int argv, char** argc){
	
	std::cout << "RUNNING APP" << std::endl; 	
	if(!glfwInit()){
		std::cout << "GLFW INITIALIZAION FAILED" << std::endl;
		return -1; 
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_DECORATED,GLFW_TRUE);
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	GLFWwindow* window = glfwCreateWindow(mode->width,mode->height,"Editor",NULL,NULL);
		if(!window){
		std::cout << "WINDOW CREATION FAILED" << std::endl; 
		glfwTerminate(); 
		return -1; 
	}
	
	glfwMakeContextCurrent(window);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	std::filesystem::path newPath("data"); 
	std::filesystem::current_path(newPath);	
	
	while(!glfwWindowShouldClose(window)){
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); 
		ImGui::NewFrame();
			
		ImGuiViewport* viewport = ImGui::GetMainViewport(); 
		ImVec2 size = viewport->Size; 
		ImVec2 position = viewport->Pos; 
		
		// Left Panel	
		ObjectBrowserWindow objectBrowserWindow(size,position); 
		objectBrowserWindow.Render(); 	

		// Right panel - top half
		FileBrowserWindow browserWindow(size,position);
		browserWindow.Render(); 	
				
		// Left panel - bottom half
		InputWindow inputWindow(size,position);
		inputWindow.Render(); 

		ImGui::Render(); 	
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	} 
	
	glfwTerminate(); 
	std::cout << "EXIT SUCCESSFULLY" << std::endl; 	
	return 0;		

}
