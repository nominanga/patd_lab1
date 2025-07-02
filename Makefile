CC = gcc
CFLAGS = -Wall -Wextra -g -DUNITY_INCLUDE_DOUBLE

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = tests/unity

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/matrix.c \
      $(SRC_DIR)/types.c \
      $(SRC_DIR)/complex.c

TEST_SRC = $(TEST_DIR)/UnitTests.c $(UNITY_DIR)/unity.c
TEST_OBJ = $(TEST_SRC:.c=.o)

OBJ = $(SRC:.c=.o)
TARGET = main
TEST_EXEC = test_runner

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)

$(TEST_EXEC): $(filter-out $(SRC_DIR)/main.o, $(OBJ)) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

run-tests: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_EXEC)

.PHONY: all clean test run-tests
