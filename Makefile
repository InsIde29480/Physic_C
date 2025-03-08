CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra -g
LDFLAGS = $(shell sdl2-config --libs)

# Define the output target (your executable name)
TARGET = Physic

# Collect all the .c files in the directory (your source files)
SRC = $(wildcard *.c)

# Default target
all: $(TARGET)

# Rule for building the target executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean target to remove the generated files
clean:
	rm -f $(TARGET)