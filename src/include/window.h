
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Window {
  GLFWwindow *window;

  unsigned int width;
  unsigned int height;
  
  char *title;
};

struct Window *initWindow(const char *title, const unsigned int width, const unsigned int height, const unsigned int major, const unsigned int minor);

#endif // WINDOW_H
