TARGET = executable
DIRS = src
LDLIBS = Dependencies/GLEW/lib/Release/x64/glew32.lib Dependencies/GLFW/include/lib-vs2022/glfw3.lib

#VPATH = src

CXX = g++

CXXFLAGS= -g -Wall -std=c++17 -pthread -isystem Dependencies/GLEW/include -isystem Dependencies/GLFW/include
EXEFLAGS= -Wall #-g

# this ensures that if there is a file called default, all or clean, it will still be compiled
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