#Files that will be compiled
#OBJS = shader.cpp main.cpp glad.c
OBJS = main.cpp

#Used compiler
CC = g++

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS = 

#Specifies which libraries we're linking
LINKER_FLAGS = -lglfw3 -lOpenGL32

#Executable name
EXE_NAME = galaxian

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)