#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    Object(std::string, float, float, float, float);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    std::vector<Object*> children;
    int level;
    Object* parent;
    glm::mat4 GetModel();
    glm::mat4 model;

  private:
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
