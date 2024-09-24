TARGET ?= main
TEST_TARGET ?= test

INCDIRS := include
SUB_DIR := src
TEST_DIR := output
			
INCLUDE := $(patsubst %, -I %, $(INCDIRS))						
CPPFILES := $(foreach dir, $(SUB_DIR), $(wildcard $(dir)/*.cpp))
TESTSRC := $(foreach dir, $(TEST_DIR), $(wildcard $(dir)/*.cpp))

CFLAGS := -O3 -std=c++17 -I$(INCLUDE_PATH) -B$(SOURCE_PATH)
CC := g++

.PHONY: clean build

all: clean build

$(TARGET): $(CPPFILES)
	$(CC) $(CFLAGS) -o $@ $<
	./$@

$(TEST_TARGET): $(TESTSRC)
	$(CC) $(CFLAGS) -o $@ $<
	./$@


build: $(TARGET) Makefile

clean:
	rm -rf  $(OBJ_DIR )/*.o 
	rm -rf  $(TARGET)
