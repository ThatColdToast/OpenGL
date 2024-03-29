# Include Dirs
# -idirafter
# -isystem
# -iquote

# Linker Dirs
# -L
# Linker Flags
# -l

PROJECT = OpenGL
TARGET = $(PROJECT)/Application.exe
LDLIBS = Dependencies/GLEW/lib/Release/x64/glew32s.lib Dependencies/GLFW/lib-mingw-w64/glfw3.dll -lopengl32

# LDLIBS = -LDependencies/GLEW/lib/Release/x64 -LDependencies/GLFW/lib-vc2022 -lglew32 -lglfw3
# LDLIBS = -LDependencies/GLEW/lib/Release/x64 -LDependencies/GLFW/lib-mingw-w64 -lglew32 -lglfw3
#-rpathDependencies/GLFW/lib-vc2022

# LDLIBS = -L./Dependencies/GLEW/lib/Release/x64 -L./Dependencies/GLFW/lib-vc2022 -lglew32.lib -lglfw3.lib

# LDLIBS = -l Dependencies/GLEW/lib/Release/x64/glew32.lib -l Dependencies/GLFW/lib-vc2022/glfw3.lib

#VPATH = src

CXX = g++



.PHONY: compile run clean
# .PHONY: debug release compile run run-debug run-release clean

# Debug
# debug: $(TARGET)
CXXFLAGS= -Wall -std=c++17 -g -Og -fdata-sections -ffunction-sections -iquote OpenGL/src -isystem Dependencies/GLEW/include -isystem Dependencies/GLFW/include -isystem OpenGL/src/vendor -I OpenGL/src/vendor/imgui -I OpenGL/src/vendor/stb_image
EXEFLAGS = -Wl,--gc-sections

# Release
# release: $(TARGET) clean
# CXXFLAGS= -Wall -std=c++17 -O3 -fdata-sections -ffunction-sections -iquote OpenGL/src -isystem Dependencies/GLEW/include -isystem Dependencies/GLFW/include -isystem OpenGL/src/vendor -I OpenGL/src/vendor/imgui -I OpenGL/src/vendor/stb_image
# EXEFLAGS = -Wl,--gc-sections

# As is (not recommended)
compile: $(TARGET)

run: compile
	./$(TARGET)

# run-debug: debug
# 	./$(TARGET)

# run-release: release
# 	./$(TARGET)


ifeq ($(OS),Windows_NT) # Windows
clean:
	rm -f $(shell powershell /C dir -Include *.o -Recurse -Name)
	rm -f $(shell powershell /C dir -Include *.exe -Recurse -Name)
#	Remove-Item '*' -Recurse -Include *.o
#	Remove-Item '*' -Recurse -Include *.exe
else # Linux/MacOS/Unix/BSD
clean:
	rm -f $(shell find . -type f -name "*.o")
	rm -f $(shell find . -type f -name "*.exe")
endif

SRCS:=

# substitute '.cpp' with '.o' in any *.cpp
ifeq ($(OS),Windows_NT)
#	@echo Windows
	SRCS += $(shell powershell /C dir -Include *.cpp -Recurse -Name)
else
#	@echo Linux/MacOS/Unix/BSD
	SRCS += $(shell find . -type f -name "*.cpp")
endif

OBJECTS := $(patsubst %.cpp, %.o, $(SRCS))
# OBJECTS := $(patsubst %src, %out, $(patsubst %.cpp, %.o, $(SRCS)))
#HEADERS := $(wildcard *.h)

# build the executable
%.o: %.cpp# $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
# if make is interupted, dont delete any object files
.PRECIOUS: $(TARGET) $(OBJECTS)

# build the objects
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDLIBS) $(EXEFLAGS) -o $@