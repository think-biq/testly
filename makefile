# -*- coding: utf8 -*-

FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR := $(shell dirname $(FILE_PATH))
PROJECT_NAME := $(notdir $(patsubst %/,%,$(dir $(FILE_PATH))))
BUILD_DIR := "$(PROJECT_DIR)/staging"
WITH_TEST := 1
GRIND = valgrind
GRIND_OPTS = --show-leak-kinds=all --leak-check=full --track-origins=yes -v
BUILD_MODE = Release

default: all

debug:
	@echo "FILE_PATH: $(FILE_PATH)"
	@echo "PROJECT_DIR: $(PROJECT_DIR)"
	@echo "PROJECT_NAME: $(PROJECT_NAME)"

clean:
	@rm -rf "$(BUILD_DIR)"

prepare:
	@mkdir -p "$(BUILD_DIR)"
	@(cd $(BUILD_DIR) && cmake -D Testly_WithTest=${WITH_TEST} -D CMAKE_BUILD_TYPE=${BUILD_MODE} ..)

build:
	@make -C "$(BUILD_DIR)"

run-test:
	@(([ ${WITH_TEST} = 1 ] && [ -f "$(BUILD_DIR)/TestlyTest" ]) \
		&& "$(BUILD_DIR)/./TestlyTest" ) || echo Skipping test ...

docs: clean-docs
	doxygen docs/doxygen.cfg > docs/doxygen.log 2> docs/doxygen.err.log

open-docs:
	open docs/html/index.html

clean-docs:
	rm -rf docs/{html,latex}
	rm -f docs/doxygen*.log

build-run: build run-test

all: prepare build-run

grind:
	mkdir -p log
	$(GRIND) $(GRIND_OPTS) "$(BUILD_DIR)/./ShaOneTest" > log/debug 2> log/error

