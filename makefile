CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

TARGET := brsh

SRC_DIR := src
BUILD_DIR := build

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	clear
	./$(BUILD_DIR)/$(TARGET)

.PHONY: debug
debug: CXXFLAGS += -g
debug: $(TARGET)
	clear
	lldb ./$(BUILD_DIR)/$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)