CXX := g++
CFLAGS := -Iinclude -Wall

SRC := $(shell find src -name "*.cpp")
DEPENDENCE := -lCerealShell
GTKLIB = $(pkg-config gtkmm-4.0 --cflags --libs)

BUILD_DIR := build
TEST_OUT := teste

TEST_TARGET := test.cpp
MAIN_TARGET := main.cpp

test: $(BUILD_DIR) $(TEST_TARGET)
	$(CXX) $(TEST_TARGET) $(SRC) $(CFLAGS) $(DEPENDENCE) -o $(BUILD_DIR)/$(TEST_OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
