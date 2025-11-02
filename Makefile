CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g

BUILD_DIR = build
SRC_DIR = src

SRCS = $(shell find src -type f -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = build/weatherAnalyzer

build: $(TARGET)

$(TARGET): $(OBJS) 
	@mkdir -p $(BUILD_DIR)
	@echo $(BUILD_DIR)/$(addprefix $(BUILD_DIR)/,$(notdir $^))
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD_DIR)/,$(notdir $^))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $(BUILD_DIR)/$(notdir $@)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
