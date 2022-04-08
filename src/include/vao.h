
#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VAO {
    unsigned int id;

    void (*bind)(struct VAO *vao);
    void (*unbind)();
};

struct VAO *initVAO();

#endif // VAO_H