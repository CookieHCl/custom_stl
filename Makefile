# === Config ===
CXX ?= g++
CXXFLAGS ?= -O2 -Wall -std=gnu++20

TARGET ?= main
ifeq ($(OS),Windows_NT)
	TARGET_EXT := .exe
else
	TARGET_EXT :=
endif

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build/obj
BUILD_DIR := build

# === Files ===
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

OUT := $(BUILD_DIR)/$(TARGET)$(TARGET_EXT)

# === Targets ===
.PHONY: build run clean

default: run

build: $(OUT)

run: $(OUT)
	@echo "Running executable..."
	@./$(OUT) < input.txt

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)

# === Rules ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

$(OUT): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@