CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
TARGET = processor
BUILD_DIR = build
SRC_DIR = src

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/core/image.cpp $(SRC_DIR)/core/kernel.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/core

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
