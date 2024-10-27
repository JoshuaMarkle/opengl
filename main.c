#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// Declare functions
void processInput(GLFWwindow *window);

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return -1;
  }

  // Set GLFW options
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // for MacOS compatibility

  // Create a GLFW window
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "opengl", NULL, NULL);
  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  // Set context for GLEW and OpenGL
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    printf("Failed to initialize GLEW\n");
    return -1;
  }

  // Set OpenGL viewport
  int screenWidth, screenHeight;
  glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
  glViewport(0, 0, screenWidth, screenHeight);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Check for events
    glfwPollEvents();
    processInput(window);

    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Cleanup and close the application
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
