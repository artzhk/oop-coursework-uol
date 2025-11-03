CXX = g++
CXXFLAGS = -std=c++11 -Wpedantic -Wall -Wextra -O2 -g -MMD -MP

BUILD = build
SRC = src
BIN = bin

SRCS = $(shell find src -type f -name '*.cpp')
OBJS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))

DEPS := $(OBJS:.o=.d)

TARGET = $(BIN)/weatherAnalyzer

build: $(TARGET)

$(TARGET): $(OBJS) 
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(wildcard $(BUILD)/*.o)

$(BUILD)/%.o: $(SRC)/%.cpp 
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c $^ -o $(BUILD)/$(notdir $@)

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean

-include $(DEPS)
