CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g

BUILD = build
SRC = src
BIN = bin

SRCS = $(shell find src -type f -name '*.cpp')
OBJS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))

TARGET = $(BIN)/weatherAnalyzer

build: $(TARGET)

$(TARGET): $(OBJS) 
	@mkdir -p $(BIN)
	@echo $(BUILD)/$(addprefix $(BUILD)/,$(notdir $^))
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD)/,$(notdir $^))

$(BUILD)/%.o: $(SRC)/%.cpp 
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c $^ -o $(BUILD)/$(notdir $@)

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean
