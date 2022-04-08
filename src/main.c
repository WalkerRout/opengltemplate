#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/renderer.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800



GLFWwindow *initWindow(void);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);



int main(int argc, char *argv[]){

  struct Renderer *renderer = (struct Renderer *) malloc(sizeof(struct Renderer));

  renderer->window = initWindow();
  renderer->shaders[0] = initShader("basicVertex.vert", "basicFragment.frag");
  renderer->shaders[0]->createProgram(renderer->shaders[0]);
  
  float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, // top left
    -0.5f, -1.0f, 0.0f, // bottom mid-left
    0.5f, 1.0f, 0.0f    // top mid-right
  };

  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,   // second triangle
    1, 2, 4,   // third triangle
    0, 3, 5    // fourth triangle
  };  
 

  renderer->vaos[0] = initVAO();
  renderer->vaos[0]->bind(renderer->vaos[0]);

  renderer->vbos[0] = initVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
  renderer->vbos[0]->bind(renderer->vbos[0]);

  renderer->ebos[0] = initEBO(indices, sizeof(indices), GL_STATIC_DRAW);
  renderer->ebos[0]->bind(renderer->ebos[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  renderer->vbos[0]->unbind();
  renderer->vaos[0]->unbind();
  renderer->ebos[0]->unbind();
 
  while(!glfwWindowShouldClose(renderer->window)){
    processInput(renderer->window);
    
    //Enable Wireframe:
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderer->shaders[0]->programId);

    renderer->vaos[0]->bind(renderer->vaos[0]);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
    renderer->vaos[0]->unbind();

    glfwSwapBuffers(renderer->window);
    glfwPollEvents();
  }
  
  renderer->shaders[0]->freeShader(&renderer->shaders[0]);
  glfwTerminate();

  return 0;
}



GLFWwindow *initWindow(void){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
  
  if(window == NULL){
    fprintf(stderr, "Window is null!");
    glfwTerminate();
    exit(1);
  }
  
  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD");
    exit(1);
  }

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

  return window;
}



void framebufferSizeCallback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}



void processInput(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}
