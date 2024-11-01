# Directories
IMGUI_DIR = ./lib/imgui

# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

# Source files
SRC = main.cpp \
      $(IMGUI_DIR)/imgui.cpp \
      $(IMGUI_DIR)/imgui_draw.cpp \
      $(IMGUI_DIR)/imgui_widgets.cpp \
      $(IMGUI_DIR)/imgui_tables.cpp \
      $(IMGUI_DIR)/imgui_demo.cpp \
      $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
      $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

# Object files (replace .cpp with .o)
OBJ = $(SRC:.cpp=.o)

# Output executable
TARGET = main
LIBS = -lglfw -lGL -lGLEW

# Default target (build and run the project)
all: $(TARGET)
	@echo "Build successful. Running the program..."
	@./$(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

# Rule to build object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (not real files)
.PHONY: all clean
