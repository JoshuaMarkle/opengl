# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Source files and output
SRC = main.c
OBJ = main
LIBS = -lglfw -lGL -lGLEW

# Default target (clean, compile, and run)
all: clean $(OBJ) run

# Build target
$(OBJ): $(SRC)
	$(CC) $(SRC) -o $(OBJ) $(LIBS)

# Run target (only runs if compilation is successful)
run: $(OBJ)
	@./$(OBJ)

# Clean target
clean:
	rm -f $(OBJ)

# Phony targets (not real files)
.PHONY: all run clean
