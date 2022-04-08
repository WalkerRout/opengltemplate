
#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VBO {
    unsigned int id;

    void (*bind)(struct VBO *vbo);
    void (*unbind)();
};

struct VBO *initVBO(const void *vertices, unsigned int size, GLenum mode);

#endif // VBO_H