
#include <stdlib.h>

#include "vbo.h"



static inline void bind(struct VBO *ebo);
static inline void unbind();



struct VBO *initVBO(const void *vertices, unsigned int size, GLenum mode){
    struct VBO *vbo = NULL;

    vbo = (struct VBO *) malloc(sizeof(struct VBO));

    vbo->bind = bind;
    vbo->unbind = unbind;
    
    glGenBuffers(1, &vbo->id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, mode);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}



static inline void bind(struct VBO *vbo){
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}



static inline void unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}