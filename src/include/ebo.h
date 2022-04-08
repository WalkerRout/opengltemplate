
#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct EBO {
    unsigned int id;

    void (*bind)(struct EBO *ebo);
    void (*unbind)();
};

struct EBO *initEBO(const void *indices, unsigned int size, GLenum mode);

#endif // EBO_H