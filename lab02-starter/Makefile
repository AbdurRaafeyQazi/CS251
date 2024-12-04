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
	-std=c++2a -I. -g -fno-omit-frame-pointer

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	GTEST_PREFIX := $(shell brew --prefix googletest)
	LLVM_PREFIX := $(shell brew --prefix llvm)
	CXX := $(LLVM_PREFIX)/bin/clang++
	CXXFLAGS += -I$(GTEST_PREFIX)/include
	CXXFLAGS += -L$(GTEST_PREFIX)/lib
endif

# === Lab 2 targets ===

# dedup executable
dedup: dedup.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build and execute dedup
run_dedup: dedup
	./$<

# Concat executable
concat: concat_files.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Concat test executable
concat_tests: concat_files.cpp concat_files_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -DCOMPILED_FOR_GTEST -lgtest -lgtest_main -o $@

# Build and execute concat executable
run_concat: concat
	./$<

# Build and execute concat tests
test_concat: concat_tests
	./$<

clean:
	rm -f concat concat_tests

.PHONY: clean run_dedup run_concat test_concat
