CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
INCLUDES = -I./src/include -I./src/matrix -I./src/output -I./tests
LDFLAGS = -lm
CUNIT_LIBS = -lcunit
CLANG_FORMAT = clang-format -i --style=file

TARGET = matrix_app
TEST_TARGET = matrix_tests

SRC_DIR = src
TEST_DIR = tests
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/matrix/matrix_operations.c $(SRC_DIR)/output/output.c
TEST_SRCS = $(TEST_DIR)/tests_matrix.c $(TEST_DIR)/tests_output.c $(TEST_DIR)/test_runner.c

# All source files that should be formatted
FORMAT_SRCS = $(SRCS) $(TEST_SRCS)
FORMAT_HEADERS = $(wildcard $(SRC_DIR)/include/*.h) \
                 $(wildcard $(SRC_DIR)/matrix/*.h) \
                 $(wildcard $(SRC_DIR)/output/*.h) \
                 $(wildcard $(TEST_DIR)/*.h)

# Object files
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o) $(filter-out $(SRC_DIR)/main.o, $(OBJS))

.PHONY: all clean run test debug sanitize sanitize-test format

# Default target
all: $(TARGET)

# Main application
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(CUNIT_LIBS)

# Compile rules
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Format source code
format:
	$(CLANG_FORMAT) $(FORMAT_SRCS) $(FORMAT_HEADERS)

# Clean (добавляем удаление файлов санитайзеров)
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
	find . -name "*.asan" -delete

# Run main app
run: $(TARGET)
	./$(TARGET) data/A.txt data/B.txt data/C.txt data/D.txt

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Debug (без санитайзеров)
debug: CFLAGS := $(filter-out -fsanitize=%,$(CFLAGS))
debug: LDFLAGS := $(filter-out -fsanitize=%,$(LDFLAGS))
debug: $(TARGET)
	gdb --args ./$(TARGET) data/A.txt data/B.txt data/C.txt data/D.txt

# Sanitizers
sanitize: CFLAGS += -fsanitize=address -fsanitize=undefined
sanitize: LDFLAGS += -fsanitize=address -fsanitize=undefined
sanitize: clean $(TARGET)

sanitize-test: CFLAGS += -fsanitize=address -fsanitize=undefined
sanitize-test: LDFLAGS += -fsanitize=address -fsanitize=undefined
sanitize-test: clean $(TEST_TARGET)