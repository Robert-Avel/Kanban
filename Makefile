CXX := g++
CFLAGS := -Iinclude -Wall

SRC := $(shell find src -name "*.cpp")
DEPENDENCE := -lCerealShell -lByteS
GTKLIB = $(shell pkg-config gtkmm-4.0 --cflags --libs)

BUILD_DIR := build
TEST_OUT := test
MAIN_OUT := main

TEST_TARGET := test.cpp
MAIN_TARGET := main.cpp

main:$(BUILD_DIR) $(MAIN_TARGET)
	$(CXX) $(MAIN_TARGET) $(SRC) $(CFLAGS) $(DEPENDENCE) $(GTKLIB) -o $(BUILD_DIR)/$(MAIN_OUT) -g

test: $(BUILD_DIR) $(TEST_TARGET)
	$(CXX) $(TEST_TARGET) $(SRC) $(CFLAGS) $(DEPENDENCE) $(GTKLIB) -o $(BUILD_DIR)/$(TEST_OUT) -g

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
