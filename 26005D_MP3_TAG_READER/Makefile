CC := gcc
CFLAGS := -Wall -Wextra -std=c11
TARGET := mp3_tag_reader
SOURCES := main.c view.c edit.c
HEADERS := view.h edit.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
