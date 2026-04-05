buildDirectory = ./build
sourceDirectory = ./src
thirdPartyDirectory = ./third_party/imgui
buildFiles = $(sourceDirectory)/main.cpp \
	     third_party/imgui/imgui.cpp \
	     third_party/imgui/imgui_draw.cpp \
	     third_party/imgui/imgui_tables.cpp \
	     third_party/imgui/imgui_widgets.cpp \
	     third_party/imgui/backends/imgui_impl_glfw.cpp \
	     third_party/imgui/backends/imgui_impl_opengl3.cpp \

executable = $(buildDirectory)/main
compileOptions =-std=c++17 -I/opt/homebrew/opt/glfw/include \
		-Ithird_party/imgui \
		-Ithird_party/imgui/backends \
		-L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL\
		-framework Cocoa -framework IOKit -framework CoreVideo -o  

build: $(executable)
	$(executable)
	make clean

clean: 
	rm -f $(executable)

$(executable): $(buildFiles)
	g++ $(buildFiles) $(compileOptions) $(executable)
