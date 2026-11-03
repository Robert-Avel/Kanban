CXX := g++
CFLAGS := -Iinclude -Wall

SRC := $(shell find src -name "*.cpp")
DEPENDENCE := -lCerealShell -lByteS
GTKLIB = $(pkg-config gtkmm-4.0 --cflags --libs)

BUILD_DIR := build
TEST_OUT := teste
MAIN_OUT := main

TEST_TARGET := test.cpp
MAIN_TARGET := main.cpp

main:$(BUILD_DIR) $(MAIN_TARGET)
	$(CXX) $(MAIN_TARGET) $(SRC) $(CFLAGS) $(DEPENDENCE) -o $(BUILD_DIR)/$(MAIN_OUT)

test: $(BUILD_DIR) $(TEST_TARGET)
	$(CXX) $(TEST_TARGET) $(SRC) $(CFLAGS) $(DEPENDENCE) -o $(BUILD_DIR)/$(TEST_OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
