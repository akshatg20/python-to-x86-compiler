# Compiler
CC = g++ -std=c++11

# Compiler flags
CFLAGS_MAC = -Wno-deprecated -g
CFLAGS =

# Source files
# SRCS = gen_3ac.cpp symbol_table.cpp ast.cpp parse.tab.c
# Use the below ```SRCS``` when the whole project is ready
SRCS = gen_x86.cpp gen_3ac.cpp symbol_table.cpp ast.cpp types.cpp parse.tab.c

# Header files
# HDRS = gen_3ac.hpp symbol_table.hpp ast.hpp utils.hpp
# Use the below ```HDRS``` when the whole project is ready
HDRS = gen_x86.hpp gen_3ac.hpp symbol_table.hpp ast.hpp types.hpp utils.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = cs335

# Check the machine on which program is being executed
OS := $(shell uname)

# Default target
all: $(TARGET)

# Compile .cpp files to object files
ifeq ($(OS), Darwin)
    # Commands to run on macOS
    %.o: %.cpp
		  $(CC) $(CFLAGS_MAC) -c $< -o $@
else
    # Commands to run on other OS
    %.o: %.cpp
		  $(CC) $(CFLAGS) -c $< -o $@
endif

# Compile lex file to C file
lex.yy.c: scan.l parse.tab.c
	flex scan.l

# Compile parser
parse.tab.c: parse.y
	bison -d parse.y

# Link object files to generate executable
ifeq ($(OS), Darwin)
    # Commands to run on macOS
    $(TARGET): lex.yy.c parse.tab.c $(OBJS) main.cpp
		  $(CC) $(CFLAGS_MAC) -o $@ $^
else
    # Commands to run on other OS
    $(TARGET): lex.yy.c parse.tab.c $(OBJS) main.cpp
		  $(CC) $(CFLAGS) -o $@ $^
endif

# Clean up
clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parse.tab.h

# Phony targets
.PHONY: all clean
