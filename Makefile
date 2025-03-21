# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Ilib/cli -Ilib/algorithms  -Ilib/parsers -Ilib/utils
LDFLAGS = 

DEBUG_FLAGS = -g


# Find all source files recursively
SRCS = main.c $(wildcard lib/cli/*.c) $(wildcard lib/algorithms/*.c)  $(wildcard lib/parsers/*.c) $(wildcard lib/utils/*.c)
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = main 

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Rule to compile source files into object files
# Adjust output path to match object location
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run debug build
run-debug: debug
	./$(TARGET)

test: 
	./$(TARGET) -c chunks.txt -s sizes.txt -a best_fit

next_fit:
	./$(TARGET) -c x1 -s x2 -a next_fit  > next_fit.txt

first_fit:
	./$(TARGET) -c x1 -s x2 -a first_fit  > first_fit.txt

run_all:
	./$(TARGET) -c x1 -s x2 -a next_fit  > next_fit.txt
	./$(TARGET) -c x1 -s x2 -a first_fit  > first_fit.txt
	./$(TARGET) -c x1 -s x2 -a best_fit  > best_fit.txt
	./$(TARGET) -c x1 -s x2 -a worst_fit  > worst_fit.txt


# Phony targets to avoid conflicts with file names
.PHONY: clean run
