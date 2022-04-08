
#include <stdlib.h>

#include "vao.h"



static inline void bind(struct VAO *vao);
static inline void unbind();



struct VAO *initVAO(){
    struct VAO *vao = NULL;

    vao = (struct VAO *) malloc(sizeof(struct VAO));

    vao->bind = bind;
    vao->unbind = unbind;

    glGenVertexArrays(1, &vao->id);
    glBindVertexArray(0);
    
    return vao;
}



static inline void bind(struct VAO *vao){
    glBindVertexArray(vao->id);
}



static inline void unbind(){
    glBindVertexArray(0);
}