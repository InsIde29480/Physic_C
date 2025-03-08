CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra -g
LDFLAGS = $(shell sdl2-config --libs)

TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
