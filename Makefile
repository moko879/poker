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

CFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I /usr/local/include
LDFLAGS = -lstdc++
GTEST_LIBS = /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a  /usr/local/lib/libgmock.a

.PHONY: clean all build test build_test

all: build test

build: $(BINS)

test: build_test
	@$(BIN_DIR)/all_test

build_test: $(TEST_BINS) $(BIN_DIR)/all_test

-include $(DEPS)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -MM -MD -MP -MT $(@:.d=.o) >$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(OBJ_DIR)/%.d
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDFLAGS)

# Note: if this project gets larger we may need to spell out test dependencies explicitly
$(BIN_DIR)/%_test: $(OBJ_DIR)/%_test.o $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)

# Note: if this project gets larger it may not be efficient to merge all the tests into 1
$(BIN_DIR)/all_test: $(OBJS)
	@mkdir -p $(BIN_DIR)
	echo $(CC) $(CFLAGS) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)
	$(CC) $(CFLAGS) -o $@ $^  $(GTEST_LIBS) $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/*.d
	rm -f $(BIN_DIR)/*_test
	rm -f $(BINS)