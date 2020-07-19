CC = g++
SRC_DIR = .
OBJ_DIR = .obj
BIN_DIR = bin

TEST_SRCS = $(shell find $(SRC_DIR) -name "*_test.cc")
TEST_OBJS = $(TEST_SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)
TEST_BINS = $(TEST_SRCS:$(SRC_DIR)/%.cc=$(BIN_DIR)/%)

BINS =

SRCS = $(shell find ${SRC_DIR} -name "*.cc")
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# TODO: cache the current build flags as a dependency so we rebuild everything on changes
CFLAGS = -std=c++17 -Wall -Wextra -g $(COV_CFLAGS)
COVFLAGS = --rc lcov_branch_coverage=1
INCLUDES = -I /usr/local/include -I .
LDFLAGS =
GTEST_LIBS = /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a  /usr/local/lib/libgmock.a

.PHONY: clean all build test build_test cov

all: build test

build: $(BINS)

test: build_test
	@$(BIN_DIR)/all_test

build_test: $(TEST_BINS) $(BIN_DIR)/all_test

cov:
	rm -rf coverage_report
	lcov --zerocounters --directory . $(COVFLAGS)
	$(MAKE) COV_CFLAGS="-coverage -g -O0" test
	lcov --capture --directory . --base-directory . -o coverage.out $(COVFLAGS)
	lcov --remove coverage.out "/usr/local*" -o coverage.out $(COVFLAGS)
	lcov --remove coverage.out "*usr/include*" -o coverage.out $(COVFLAGS)
	lcov --remove coverage.out "*_test.cc" -o coverage.out $(COVFLAGS)
	genhtml -o coverage_report coverage.out $(COVFLAGS)
	rm coverage.out
	open coverage_report/index.html

-include $(DEPS)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $< -MM -MP -MT $(@:.d=.o) >$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(OBJ_DIR)/%.d
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDFLAGS)

# Note: if this project gets larger we may need to spell out test dependencies explicitly
$(BIN_DIR)/%_test: $(OBJ_DIR)/%_test.o $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)

# Note: if this project gets larger it may not be efficient to merge all the tests into 1
$(BIN_DIR)/all_test: $(OBJS)
	@mkdir -p $(dir $@)
	echo $(CC) $(CFLAGS) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)

clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*.gcno' -delete
	find . -name '*.gcda' -delete
	find . -name '*_test' -delete
	find . -type d -empty -delete
	find . -type d -empty -delete
	rm -f $(BINS)
	# Delete directories
