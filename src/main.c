#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/renderer.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800



void processInput(GLFWwindow *window);



int main(int argc, char *argv[]){

  struct Renderer *renderer = (struct Renderer *) malloc(sizeof(struct Renderer));

  renderer->window = initWindow("OpenGL Template", SCREEN_WIDTH, SCREEN_HEIGHT, 3, 3);
  renderer->shaders[0] = initShader("basicVertex.vert", "basicFragment.frag");
  renderer->shaders[0]->createProgram(renderer->shaders[0]);

  float vertices[] = {
    -0.5f, -0.5f * (float) sqrt(3) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * (float) sqrt(3) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * (float) sqrt(3) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * (float) sqrt(3) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * (float) sqrt(3) / 6, 0.0f, // Inner right
    0.0f, -0.5f * (float) sqrt(3) / 3, 0.0f // Inner down
  };

  unsigned int indices[] = {  // note that we start from 0!
    0, 3, 5,   // first triangle
    3, 2, 4,   // second triangle
    5, 4, 1,   // third triangle
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
 
  while(!glfwWindowShouldClose(renderer->window->window)){
    processInput(renderer->window->window);
    
    //Enable Wireframe:
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderer->shaders[0]->programId);

    renderer->vaos[0]->bind(renderer->vaos[0]);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
    renderer->vaos[0]->unbind();

    glfwSwapBuffers(renderer->window->window);
    glfwPollEvents();
  }
  
  renderer->shaders[0]->freeShader(&renderer->shaders[0]);
  glfwTerminate();

  return 0;
}



void processInput(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}
