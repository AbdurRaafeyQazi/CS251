CXX = clang++
CXXFLAGS = \
	-Wall -Wextra -Werror \
	-Wno-error=unused-function \
	-Wno-error=unused-parameter \
	-Wno-error=unused-variable \
	-Wno-error=unused-but-set-variable \
	-Wno-error=unused-value \
	-Wno-sign-compare \
	-Wno-unused-command-line-argument \
	-std=c++2a -I. -g -fno-omit-frame-pointer \
	-fsanitize=address,undefined

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	GTEST_PREFIX := $(shell brew --prefix googletest)
	LLVM_PREFIX := $(shell brew --prefix llvm)
	CXX := $(LLVM_PREFIX)/bin/clang++
	CXXFLAGS += -I$(GTEST_PREFIX)/include
	CXXFLAGS += -L$(GTEST_PREFIX)/lib
endif

# === Main targets ===

# Main executable
main: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Main test executable
main_tests: main.cpp main_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -DCOMPILED_FOR_GTEST -lgtest -lgtest_main -o $@

# Build and execute main executable
run_main: main
	./$<

# Build and execute main tests
test_main: main_tests
	./$<

# === Lab 1 targets ===

lab1: lab1.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Lab 1 test executable
lab1_tests: lab1.cpp lab1_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -DCOMPILED_FOR_GTEST -lgtest -lgtest_main -o $@

# Build and execute lab 1 executable
run_lab1: lab1
	./$<

# Build and execute lab 1 tests
test_lab1: lab1_tests
	./$<

clean:
	rm -f main main_tests lab1 lab1_tests

.PHONY: clean run_main test_main run_lab1 test_lab1
