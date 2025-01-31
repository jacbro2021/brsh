# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g

# Target executable
TARGET := brsh

# Source files (add more as needed)
SRCS := brsh.cpp parse.cpp

# Object files (derived from source files)
OBJS := $(SRCS:.cpp=.o)

# Default rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the shell
.PHONY: run
run: $(TARGET)
	clear
	./$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)