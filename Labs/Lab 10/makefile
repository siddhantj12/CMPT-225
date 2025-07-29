# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -pedantic -Wall -Wextra -std=c++17

# Target executable
TARGET = sorting

# For deleting the target (Windows)
TARGET_DEL = sorting.exe

# Source files (only .cpp, headers are included automatically)
SRCS = sorting.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run:
	./$(TARGET)

# Clean rule to remove generated files for Windows
clean:
	del $(TARGET_DEL) $(OBJS)

# Clean rule for Linux and macOS
remove:
	\rm -f $(TARGET) $(OBJS)
