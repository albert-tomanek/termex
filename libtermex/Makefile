TARGET = termex
LIBS =
CC = gcc
CFLAGS = -ltermbox -g -O0 -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = widget.o  button.o  misc.o
HEADERS = widget.hh button.hh misc.h  chars.h

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
