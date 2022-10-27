TARGET = executable
DIRS = src
LDLIBS = -L/Dependencies/GLEW/lib/Release/x64 -L/Dependencies/GLFW/lib-vc2022 -lglew32.lib -lglfw3.lib
# LDLIBS = -l Dependencies/GLEW/lib/Release/x64/glew32.lib -l Dependencies/GLFW/lib-vc2022/glfw3.lib

#VPATH = src

CXX = g++

CXXFLAGS= -g -Wall -std=c++17 -isystem Dependencies/GLEW/include -isystem Dependencies/GLFW/include -isystem OpenGL/src/vendor -I OpenGL/src/vendor/imgui -iquote OpenGL/src
.PHONY: default compile clean run

default: $(TARGET)
	./$(TARGET)

compile: $(TARGET)

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
#HEADERS := $(wildcard *.h)

# build the executable
%.o: %.cpp# $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
# if make is interupted, dont delete any object files
.PRECIOUS: $(TARGET) $(OBJECTS)

# build the objects
$(TARGET): $(OBJECTS)
	@echo OBJS $(OBJECTS)
	$(CXX) $(OBJECTS) $(EXEFLAGS) $(LDLIBS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

# Include Dirs
# -idirafter
# -isystem
# -iquote

# Linker Dirs
# -L
# Linker Flags
# -l