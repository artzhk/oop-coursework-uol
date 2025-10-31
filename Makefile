CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g

BUILD_DIR = build
SRC_DIR = src

SRCS := $(shell find src -type f -name '*.cpp')
OBJS := $(subst $(SRC_DIR),$(BUILD_DIR),$(addsuffix .o, $(basename $(SRC))))

TARGET = build/weatherAnalyzer

build: $(TARGET)

$(TARGET): $(OBJS) 
	@mkdir -p $(BUILD_DIR)
	@echo $(OBJS)
	@echo $(basename $(SRCS))
	$(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@mkdir -p $(BUILD_DIR)
	echo "$^,$@"
	$(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
