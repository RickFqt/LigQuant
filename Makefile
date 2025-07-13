# Makefile for LigueQuant Game

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -O2
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
LDFLAGS = 

# Source files
C_SOURCES = src/LigueQuant_i.c src/LigueQuant_ctx_i.c
CXX_SOURCES = src/main.cpp
HEADERS = src/LigueQuant.h src/LigueQuant_ctx.h

# Object files
C_OBJECTS = $(C_SOURCES:.c=.o)
CXX_OBJECTS = $(CXX_SOURCES:.cpp=.o)
OBJECTS = $(C_OBJECTS) $(CXX_OBJECTS)

# Target executable
TARGET = liguequant

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile C source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Debug version
debug: CFLAGS += -g -DDEBUG
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Install dependencies (if needed)
install-deps:
	@echo "No external dependencies required"

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the game (default)"
	@echo "  clean    - Remove object files and executable"
	@echo "  run      - Build and run the game"
	@echo "  debug    - Build debug version"
	@echo "  help     - Show this help message"