TARGET ?= main
TEST_TARGET ?= test

INCDIRS := include
SUB_DIR := src
TEST_DIR := output
			
INCLUDE := $(patsubst %, -I %, $(INCDIRS))						
CPPFILES := $(foreach dir, $(SUB_DIR), $(wildcard $(dir)/*.cpp))
TESTSRC := $(TEST_DIR)/main.cpp

CFLAGS := -O3 -std=c++17
CC := g++

.PHONY: clean build

all: clean build

$(TARGET): $(CPPFILES)
	$(CC) $(CFLAGS) -o $@ $<
	./$@

$(TEST_TARGET): $(TESTSRC)
	$(CC) $(CFLAGS) -o $@ $<



build: $(TARGET) Makefile

clean:
	rm -rf  $(OBJ_DIR )/*.o 
	rm -rf  $(TARGET)
