TARGET = Interpreter
LIBS = -lm -lwiringPi
CC = gcc
CFLAGS = -g -Wall -std=c99

.PHONY: default all clean

default: $(TARGET)
all: default
debug: 

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)