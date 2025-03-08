# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Ilib/cli -Ilib/algorithms
LDFLAGS = 

# Find all source files recursively
SRCS = main.c $(wildcard lib/cli/*.c) $(wildcard lib/algorithms/*.c)
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = main 

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

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

test: 
	./$(TARGET) -c chunks.txt -s sizes.txt

# Phony targets to avoid conflicts with file names
.PHONY: clean run
