
#include <stdlib.h>

#include "ebo.h"



static inline void bind(struct EBO *ebo);
static inline void unbind();



struct EBO *initEBO(const void *indices, unsigned int size, GLenum mode){
    struct EBO *ebo = NULL;

    ebo = (struct EBO *) malloc(sizeof(struct EBO));

    ebo->bind = bind;
    ebo->unbind = unbind;
    
    glGenBuffers(1, &ebo->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, mode);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return ebo;
}



static inline void bind(struct EBO *ebo){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
}



static inline void unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}