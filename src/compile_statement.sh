#!/bin/bash

g++ -std=c++17 main.cpp -I/opt/homebrew/opt/glfw/include -L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -o my_window
./my_window
rm my_window
