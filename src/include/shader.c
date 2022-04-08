
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"


static void createProgram(struct Shader *shader);
static void deleteShaderIds(struct Shader *shader);
static void freeShader(struct Shader **shader);
static void shaderCompilationStatus(unsigned int shader);
static char *fileToCStr(const char *filePath);



struct Shader *initShader(const char *vertexPath, const char *fragmentPath){
  // Variable declarations
  struct Shader *shader;
  unsigned int vertexPathLength, fragmentPathLength;
  char *vertexShaderSource, *fragmentShaderSource;

  // Variable assignment
  shader = (struct Shader *) malloc(sizeof(struct Shader));
  vertexPathLength = strlen(vertexPath);
  fragmentPathLength = strlen(fragmentPath);
  vertexShaderSource = fileToCStr(vertexPath);
  fragmentShaderSource = fileToCStr(fragmentPath);

  // Shader struct initialization
  shader->vertexPath = (char *) malloc(vertexPathLength);
  strcpy(shader->vertexPath, vertexPath);
  shader->fragmentPath = (char *) malloc(fragmentPathLength);
  strcpy(shader->fragmentPath, fragmentPath);
  
  shader->vertexId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader->vertexId, 1, (const char *const *) &vertexShaderSource, NULL);
  glCompileShader(shader->vertexId);
  shaderCompilationStatus(shader->vertexId);
  shader->fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader->fragmentId, 1, (const char *const *) &fragmentShaderSource, NULL);
  glCompileShader(shader->fragmentId);
  shaderCompilationStatus(shader->fragmentId);
  
  free(vertexShaderSource);
  free(fragmentShaderSource);

  shader->createProgram = createProgram;
  shader->deleteShaderIds = deleteShaderIds;
  shader->freeShader = freeShader;

  return shader;
}



static void createProgram(struct Shader *shader){
  if(!shader){
    fprintf(stderr, "The shader passed to createProgram() has not been initialized!");
    exit(1);
  }

  shader->programId = glCreateProgram();
  glAttachShader(shader->programId, shader->vertexId);
  glAttachShader(shader->programId, shader->fragmentId);
  glLinkProgram(shader->programId);
}



static void deleteShaderIds(struct Shader *shader){
  if(!shader){
    fprintf(stderr, "The shader passed to deleteShaderObjs() has not been initialized!");
    exit(1);
  }

  glDeleteShader(shader->vertexId);
  glDeleteShader(shader->fragmentId);
}



static void freeShader(struct Shader **shader){
  if(!(*shader)){
    fprintf(stderr, "The shader passed to freeShader() has not been initialized!");
    exit(1); // only use on initialized shaders
  }

  if((*shader)->vertexPath) free((*shader)->vertexPath);
  if((*shader)->fragmentPath) free((*shader)->fragmentPath);

  if(glIsShader((*shader)->vertexId)) glDeleteShader((*shader)->vertexId);
  if(glIsShader((*shader)->fragmentId)) glDeleteShader((*shader)->fragmentId);
  if(glIsProgram((*shader)->programId)) glDeleteProgram((*shader)->programId);

  (*shader)->createProgram = NULL;
  (*shader)->deleteShaderIds = NULL;
  (*shader)->freeShader = NULL;

  free(*shader);
}



static char *fileToCStr(const char *filePath){
  FILE *file = NULL;
  char *buffer = NULL;
  
  file = fopen(filePath, "r");
  if(file == NULL) goto fail;
  if(fseek(file, 0, SEEK_END) < 0) goto fail;
  
  long fileSize = ftell(file);
  if(fileSize < 0) goto fail;
  if (fseek(file, 0, SEEK_SET) < 0) goto fail;

  buffer = (char *) malloc(fileSize + 1);
  if(buffer == NULL) goto fail;

  fread(buffer, 1, fileSize, file);
  if(ferror(file)) goto fail;
  if(file) fclose(file);

  buffer[fileSize] = '\0';

  return buffer;

fail:
  if(file) fclose(file);
  if(buffer) free(buffer);

  return NULL;
}



static void shaderCompilationStatus(unsigned int shader){
  const int BUFFER_SIZE = 512;
  int success;
  char infoLog[BUFFER_SIZE];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  
  if(!success){
    glGetShaderInfoLog(shader, BUFFER_SIZE, NULL, infoLog);
    fprintf(stderr, "ERROR! Shader Compilation Failed: %s\n", infoLog);
    exit(1);
  }
}

