
#ifndef SHADER_H
#define SHADER_H

struct Shader {
  unsigned int programId;
  unsigned int vertexId;
  unsigned int fragmentId;
  
  char *vertexPath;
  char *fragmentPath;

  void (*createProgram)(struct Shader *shader);
  void (*deleteShaderIds)(struct Shader *shader);
  void (*freeShader)(struct Shader **shader);
};

struct Shader *initShader(const char *vertexPath, const char *fragmentPath);

#endif // SHADER_H
