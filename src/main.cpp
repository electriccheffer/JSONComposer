#include <iostream>
#include <GLFW/glfw3.h>
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/backends/imgui_impl_opengl3.h"
#include "../third_party/imgui/backends/imgui_impl_glfw.h"

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


	while(!glfwWindowShouldClose(window)){
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); 
		ImGui::NewFrame();
		
		ImGuiViewport* viewport = ImGui::GetMainViewport(); 
		ImVec2 size = viewport->Size; 
		ImVec2 position = viewport->Pos; 
	
		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowSize(ImVec2(size.x * 0.5f, size.y ));
		ImGui::Begin("Left-Top", nullptr, 
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Left Top Panel");
		ImGui::End();

		// Right panel - top half
		ImGui::SetNextWindowPos(ImVec2(size.x * 0.5f + position.x, position.y));
		ImGui::SetNextWindowSize(ImVec2(size.x * 0.7f, size.y * 0.5f));
		ImGui::Begin("Right-Top", nullptr, 
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Right Top Panel");
		ImGui::End();

		// Left panel - bottom half
		ImGui::SetNextWindowPos(ImVec2(position.x + size.x * 0.5f,
						 position.y + size.y * 0.5f));
		ImGui::SetNextWindowSize(ImVec2(size.x , size.y));
		ImGui::Begin("Left-Bottom", nullptr, 
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Left Bottom Panel");
		ImGui::End();	
		
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
