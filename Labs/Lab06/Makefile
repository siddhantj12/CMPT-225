# Makefile

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic

# Executable name
TARGET = tree_test

# Source files
SRCS = main.cpp BinaryTree.cpp InorderIterator.cpp PreorderIterator.cpp PostorderIterator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# for Windows and PowerShell
clean:
	del /Q $(OBJS) $(TARGET)
	@echo clean done

# for Linux and MacOS
remove:
	rm -f $(OBJS) $(TARGET)
	@echo remove done
