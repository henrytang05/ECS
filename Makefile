# Compiler and flags
CXX := g++
CXXFLAGS := -I./src -std=c++17 -Wall -Wextra -g
LDFLAGS := -lgtest -lgtest_main -pthread

# Directories
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Executables
TARGET := main
TEST_TARGET := test_runner

# Create build directory if not exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Main program
$(TARGET): $(BUILD_DIR) $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $(OBJS) main.cpp -o $(TARGET)

# Test executable
$(TEST_TARGET): $(BUILD_DIR) $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) -o $(TEST_TARGET) $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

all: $(TARGET)


.PHONY: clean test
