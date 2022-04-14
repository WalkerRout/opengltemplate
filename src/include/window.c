
#include <stdio.h>
#include <stdlib.h>

#include "window.h"



static void framebufferSizeCallback(GLFWwindow *window, int width, int height);



struct Window *initWindow(const char *title, const unsigned int width, const unsigned int height, const unsigned int major, const unsigned int minor){
  struct Window *window = (struct Window *) malloc(sizeof(struct Window));

  window->width = width;
  window->height = height;
  window->title = (char *) title;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window->window = glfwCreateWindow(width, height, title, NULL, NULL);

  if(window->window == NULL){
    fprintf(stderr, "Window is null!");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window->window);

  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD");
    exit(1);
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window->window, framebufferSizeCallback);  

  return window;
}



static void framebufferSizeCallback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}

