
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "window.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#define SHADER_CAP 16
#define VAO_CAP 16
#define VBO_CAP 16
#define EBO_CAP 16

struct Renderer {
    struct Window *window;
    
    struct Shader *shaders[SHADER_CAP];
    struct VAO *vaos[VAO_CAP];
    struct VBO *vbos[VBO_CAP];
    struct EBO *ebos[EBO_CAP];
};

struct Renderer *initRenderer();

#endif // RENDERER_H
