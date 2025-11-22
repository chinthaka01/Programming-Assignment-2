CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = bankers
SRCDIR = src
INPDIR = inputs
SOURCES = $(SRCDIR)/bankers_algorithm.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

# Run with default input file
run: $(TARGET)
	./$(TARGET) $(INPDIR)/safe_input.txt

.PHONY: clean run